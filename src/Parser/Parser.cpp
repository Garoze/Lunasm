#include <charconv>
#include <cstdint>
#include <fstream>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <string_view>
#include <variant>

#include "Lexer/Token.hpp"
#include "fmt/core.h"
#include "fmt/ranges.h"

#include "Lexer/Mnemonics.hpp"

#include "Parser/ASLL.hpp"
#include "Parser/Instruction.hpp"
#include "Parser/Label.hpp"
#include "Parser/Opcodes.hpp"
#include "Parser/Parser.hpp"

namespace Lunasm {

Parser::Parser()
    : m_index(0)
    , m_lexer(std::make_unique<Lexer>())
    , m_asll(std::make_unique<ASLL>())
{}

void Parser::step()
{
    if ((m_index + 1) < m_tokens.size())
    {
        m_index++;
    }
}

std::optional<Token> Parser::look_ahead(std::size_t pos = 0)
{
    auto index = m_index + pos;

    if (index < m_tokens.size())
    {
        return m_tokens.at(index);
    }

    return {};
}

void Parser::parse_file(std::filesystem::path const& path, bool debug)
{
    std::stringstream ss;

    const std::ifstream file(path, std::ios::in);

    if (!file.good())
    {
        auto err = fmt::format("Could not open the file {}", path.string());
        throw std::runtime_error(err);
    }

    ss << file.rdbuf();
    std::string source = ss.str();

    m_lexer->enable_debug(debug);
    m_tokens = m_lexer->Lex_source(source);

    Parse();
}

Token Parser::expect(TokenKind kind)
{
    auto t = look_ahead();
    if (t.has_value() && t->kind() == kind)
    {
        step();
        return t.value();
    }
    else
    {
        auto err =
            fmt::format("[Parser] Invalid token kind expected: '{}' got '{}'\n",
                        MNEMONICS.at(kind), look_ahead()->as_string());

        throw std::runtime_error(err);
    }
}

template <typename... Kinds>
std::optional<Token> Parser::expect_any(Kinds... kinds)
{
    static_assert((std::is_same_v<Kinds, TokenKind> && ...),
                  "must pass TokenKind values");

    auto t = look_ahead();
    if (t.has_value())
    {
        for (TokenKind k : {kinds...})
        {
            if (t->kind() == k)
            {
                step();
                return t.value();
            }
        }
    }

    return {};
}

uint8_t Parser::parse_register()
{
    auto r = expect(TokenKind::Register);

    return std::get<std::uint8_t>(r.raw_value());
}

std::uint16_t Parser::parse_immediate()
{
    auto i = expect(TokenKind::Immediate);

    return std::get<std::uint16_t>(i.raw_value());
}

std::string_view Parser::parse_label()
{
    auto label = expect(TokenKind::Label);
    expect(TokenKind::Colon);

    auto identifier = std::get<std::string_view>(label.raw_value());

    m_instructions.push_back(Label(identifier));

    return identifier;
}

Operand Parser::parse_address()
{
    expect(TokenKind::OpenBracket);

    auto addr =
        expect_any(TokenKind::Immediate, TokenKind::Register, TokenKind::Label);

    expect(TokenKind::CloseBracket);

    return addr->raw_value();
}

void Parser::handle_address(Opcode op, std::size_t size, Operand dst,
                            std::optional<Operand> src = {})
{
    auto visitor = [&](auto arg) {
        using T = std::remove_reference_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::string_view>)
        {
            m_instructions.push_back(Instruction(op, size, arg));

            m_instructions.push_back(Label(arg));
        }
        else
        {
            m_instructions.push_back(Instruction(op, size, arg));
        }
    };

    std::visit(visitor, dst);

    if (src.has_value())
    {
        std::visit(visitor, src.value());
    }
}

void Parser::nop_instruction()
{
    expect(TokenKind::NOP);
    m_instructions.push_back(Instruction(Opcode::NOP, 1));
}

void Parser::mov_instruction()
{
    expect(TokenKind::MovInstruction);

    switch (look_ahead()->kind())
    {
        case TokenKind::Register: {
            std::uint8_t dst = parse_register();
            expect(TokenKind::Comma);

            switch (look_ahead()->kind())
            {
                case TokenKind::Immediate: {
                    std::uint16_t src = parse_immediate();

                    m_instructions.push_back(
                        Instruction(Opcode::LoadImmediate, 4, dst, src));
                }
                break;

                case TokenKind::Register: {
                    auto src = parse_register();

                    m_instructions.push_back(
                        Instruction(Opcode::LoadRegister, 3, dst, src));
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();

                    handle_address(Opcode::LoadAddress, 4, dst, src);
                }
                break;

                default:
                    break;
            }
        }
        break;

        case TokenKind::OpenBracket:
            parse_address();
            expect(TokenKind::Comma);
            break;

        default:
            break;
    }
}

void Parser::shl_instruction()
{
    expect(TokenKind::ShiftLeft);
    std::uint8_t reg = parse_register();
    expect(TokenKind::Comma);
    std::uint16_t imm = parse_immediate();

    m_instructions.push_back(Instruction(Opcode::ShiftLeft, 4, reg, imm));
}

void Parser::shr_instruction()
{
    expect(TokenKind::ShiftRight);
    std::uint8_t reg = parse_register();
    expect(TokenKind::Comma);
    std::uint16_t imm = parse_immediate();

    m_instructions.push_back(Instruction(Opcode::ShiftRight, 4, reg, imm));
}

void Parser::and_instruction()
{
    expect(TokenKind::BitAND);
    std::uint8_t reg = parse_register();
    expect(TokenKind::Comma);
    std::uint16_t imm = parse_immediate();

    m_instructions.push_back(Instruction(Opcode::BitwiseAND, 4, reg, imm));
}

void Parser::bor_instruction()
{
    expect(TokenKind::BitOR);
    std::uint8_t reg = parse_register();
    expect(TokenKind::Comma);
    std::uint16_t imm = parse_immediate();

    m_instructions.push_back(Instruction(Opcode::BitwiseOR, 4, reg, imm));
}

void Parser::xor_instruction()
{
    expect(TokenKind::BitXOR);
    std::uint8_t reg = parse_register();
    expect(TokenKind::Comma);
    std::uint16_t imm = parse_immediate();

    m_instructions.push_back(Instruction(Opcode::BitwiseXOR, 4, reg, imm));
}

void Parser::not_instruction()
{
    expect(TokenKind::BitNOT);
    std::uint8_t reg = parse_register();

    m_instructions.push_back(Instruction(Opcode::BitwiseNOT, 2, reg));
}

void Parser::psh_instruction()
{
    expect(TokenKind::Push);

    switch (look_ahead()->kind())
    {
        case TokenKind::Immediate: {
            std::uint16_t src = parse_immediate();

            m_instructions.push_back(
                Instruction(Opcode::PushImmediate, 3, src));
        }
        break;

        case TokenKind::Register: {
            auto src = parse_register();

            m_instructions.push_back(Instruction(Opcode::PushRegister, 2, src));
        }
        break;

        case TokenKind::OpenBracket: {
            Operand src = parse_address();

            handle_address(Opcode::PushAddress, 3, src);
        }
        break;

        default:
            break;
    }
}

void Parser::pop_instruction()
{
    expect(TokenKind::Pop);
    std::uint8_t reg = parse_register();

    m_instructions.push_back(Instruction(Opcode::Pop, 1, reg));
}

void Parser::inc_instruction()
{
    expect(TokenKind::Increment);
    std::uint8_t reg = parse_register();

    m_instructions.push_back(Instruction(Opcode::Increment, 2, reg));
}

void Parser::dec_instruction()
{
    expect(TokenKind::Decrement);

    std::uint8_t reg = parse_register();

    m_instructions.push_back(Instruction(Opcode::Decrement, 2, reg));
}

void Parser::add_instruction()
{
    expect(TokenKind::Add);

    switch (look_ahead()->kind())
    {
        case TokenKind::Register: {
            std::uint8_t dst = parse_register();
            expect(TokenKind::Comma);

            switch (look_ahead()->kind())
            {
                case TokenKind::Immediate: {
                    std::uint16_t src = parse_immediate();

                    m_instructions.push_back(
                        Instruction(Opcode::AddImmediate, 4, dst, src));
                }
                break;

                case TokenKind::Register: {
                    auto src = parse_register();

                    m_instructions.push_back(
                        Instruction(Opcode::AddRegister, 3, dst, src));
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();

                    handle_address(Opcode::AddAddress, 4, dst, src);
                }
                break;

                default:
                    break;
            }
        }
        break;

        default:
            break;
    }
}

void Parser::sub_instruction()
{
    expect(TokenKind::Sub);

    switch (look_ahead()->kind())
    {
        case TokenKind::Register: {
            std::uint8_t dst = parse_register();
            expect(TokenKind::Comma);

            switch (look_ahead()->kind())
            {
                case TokenKind::Immediate: {
                    std::uint16_t src = parse_immediate();

                    m_instructions.push_back(
                        Instruction(Opcode::SubImmediate, 4, dst, src));
                }
                break;

                case TokenKind::Register: {
                    auto src = parse_register();

                    m_instructions.push_back(
                        Instruction(Opcode::SubRegister, 3, dst, src));
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();

                    handle_address(Opcode::SubAddress, 4, dst, src);
                }
                break;

                default:
                    break;
            }
        }
        break;

        default:
            break;
    }
}

void Parser::mul_instruction()
{
    expect(TokenKind::Mul);

    switch (look_ahead()->kind())
    {
        case TokenKind::Register: {
            std::uint8_t dst = parse_register();
            expect(TokenKind::Comma);

            switch (look_ahead()->kind())
            {
                case TokenKind::Immediate: {
                    std::uint16_t src = parse_immediate();

                    m_instructions.push_back(
                        Instruction(Opcode::MulImmediate, 4, dst, src));
                }
                break;

                case TokenKind::Register: {
                    auto src = parse_register();

                    m_instructions.push_back(
                        Instruction(Opcode::MulRegister, 3, dst, src));
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();

                    handle_address(Opcode::MulAddress, 4, dst, src);
                }
                break;

                default:
                    break;
            }
        }
        break;

        default:
            break;
    }
}

void Parser::div_instruction()
{
    expect(TokenKind::Div);

    switch (look_ahead()->kind())
    {
        case TokenKind::Register: {
            std::uint8_t dst = parse_register();
            expect(TokenKind::Comma);

            switch (look_ahead()->kind())
            {
                case TokenKind::Immediate: {
                    std::uint16_t src = parse_immediate();

                    m_instructions.push_back(
                        Instruction(Opcode::DivImmediate, 4, dst, src));
                }
                break;

                case TokenKind::Register: {
                    auto src = parse_register();

                    m_instructions.push_back(
                        Instruction(Opcode::DivRegister, 3, dst, src));
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();

                    handle_address(Opcode::DivAddress, 4, dst, src);
                }
                break;

                default:
                    break;
            }
        }
        break;

        default:
            break;
    }
}

void Parser::mod_instruction()
{
    expect(TokenKind::Mod);

    switch (look_ahead()->kind())
    {
        case TokenKind::Register: {
            std::uint8_t dst = parse_register();
            expect(TokenKind::Comma);

            switch (look_ahead()->kind())
            {
                case TokenKind::Immediate: {
                    std::uint16_t src = parse_immediate();

                    m_instructions.push_back(
                        Instruction(Opcode::ModImmediate, 4, dst, src));
                }
                break;

                case TokenKind::Register: {
                    auto src = parse_register();

                    m_instructions.push_back(
                        Instruction(Opcode::ModRegister, 3, dst, src));
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();

                    handle_address(Opcode::ModAddress, 4, dst, src);
                }
                break;

                default:
                    break;
            }
        }
        break;

        default:
            break;
    }
}

void Parser::cmp_instruction()
{
    expect(TokenKind::Compare);

    switch (look_ahead()->kind())
    {
        case TokenKind::Register: {
            std::uint8_t dst = parse_register();
            expect(TokenKind::Comma);

            switch (look_ahead()->kind())
            {
                case TokenKind::Immediate: {
                    std::uint16_t src = parse_immediate();

                    m_instructions.push_back(
                        Instruction(Opcode::CompareImmediate, 4, dst, src));
                }
                break;

                case TokenKind::Register: {
                    auto src = parse_register();

                    m_instructions.push_back(
                        Instruction(Opcode::CompareRegister, 3, dst, src));
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();

                    handle_address(Opcode::CompareAddress, 4, dst, src);
                }
                break;

                default:
                    break;
            }
        }
        break;

        default:
            break;
    }
}

void Parser::jmp_instruction()
{
    expect(TokenKind::Jump);
    Operand src = parse_address();

    handle_address(Opcode::Jump, 3, src);
}

void Parser::jeq_instruction()
{
    expect(TokenKind::JumpEquals);
    Operand src = parse_address();

    handle_address(Opcode::JumpEquals, 3, src);
}

void Parser::jne_instruction()
{
    expect(TokenKind::JumpNotEquals);
    Operand src = parse_address();

    handle_address(Opcode::JumpNotEquals, 3, src);
}

void Parser::jsr_instruction()
{
    expect(TokenKind::Subroutine);
    Operand src = parse_address();

    handle_address(Opcode::Subroutine, 3, src);
}

void Parser::ret_instruction()
{
    expect(TokenKind::Return);

    m_instructions.push_back(Instruction(Opcode::Return, 1));
}

void Parser::hlt_instruction()
{
    expect(TokenKind::Halt);

    m_instructions.push_back(Instruction(Opcode::Halt, 1));
}

void Parser::Parse()
{
    while (look_ahead()->kind() != TokenKind::END)
    {
        switch (look_ahead()->kind())
        {
            case TokenKind::Label:
                parse_label();
                break;

            case TokenKind::NOP:
                nop_instruction();
                break;

            case TokenKind::MovInstruction:
                mov_instruction();
                break;

            case TokenKind::ShiftLeft:
                shl_instruction();
                break;

            case TokenKind::ShiftRight:
                shr_instruction();
                break;

            case TokenKind::BitAND:
                and_instruction();
                break;

            case TokenKind::BitOR:
                bor_instruction();
                break;

            case TokenKind::BitXOR:
                xor_instruction();
                break;

            case TokenKind::BitNOT:
                not_instruction();
                break;

            case TokenKind::Push:
                psh_instruction();
                break;

            case TokenKind::Pop:
                pop_instruction();
                break;

            case TokenKind::Increment:
                inc_instruction();
                break;

            case TokenKind::Decrement:
                dec_instruction();
                break;

            case TokenKind::Add:
                add_instruction();
                break;

            case TokenKind::Sub:
                sub_instruction();
                break;

            case TokenKind::Mul:
                mul_instruction();
                break;

            case TokenKind::Div:
                div_instruction();
                break;

            case TokenKind::Mod:
                mod_instruction();
                break;

            case TokenKind::Compare:
                cmp_instruction();
                break;

            case TokenKind::Jump:
                jmp_instruction();
                break;

            case TokenKind::JumpEquals:
                jeq_instruction();
                break;

            case TokenKind::JumpNotEquals:
                jne_instruction();
                break;

            case TokenKind::Subroutine:
                jsr_instruction();
                break;

            case TokenKind::Return:
                ret_instruction();
                break;

            case TokenKind::Halt:
                hlt_instruction();
                break;

            default:
                fmt::print("[Parser] Unimplemented token kind: {}\n",
                           look_ahead()->as_string());
                step();
                break;
        }
    }

    // debug_instruction();
    fmt::print("[Parser] Finished the parser, no errors reported.\n");

    m_asll->handle_instructions(m_instructions);
}

} // namespace Lunasm
