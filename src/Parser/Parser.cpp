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

#include "fmt/core.h"
#include "fmt/ranges.h"

#include "Lexer/Mnemonics.hpp"
#include "Lexer/Token.hpp"

#include "Parser/ASLL.hpp"
#include "Parser/Instruction.hpp"
#include "Parser/Label.hpp"
#include "Parser/Opcodes.hpp"
#include "Parser/Parser.hpp"
#include "Parser/Sizes.hpp"

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
    auto l = expect(TokenKind::Label);
    expect(TokenKind::Colon);

    auto identifier = std::get<std::string_view>(l.raw_value());

    m_instructions.push_back(Label(identifier));

    // fmt::print("[Parser] Label definition: `{}`\n", identifier);

    return identifier;
}

Operand Parser::parse_address()
{
    expect(TokenKind::OpenBracket);

    auto a =
        expect_any(TokenKind::Immediate, TokenKind::Register, TokenKind::Label);

    expect(TokenKind::CloseBracket);

    return a->raw_value();
}

void Parser::push_instruction(Opcode op, Operand dst = {}, Operand src = {})
{
    m_instructions.push_back(Instruction{op, INST_SIZE.at(op), dst, src});
}

void Parser::nop_instruction()
{
    expect(TokenKind::NOP);
    push_instruction(Opcode::NOP);
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
                    push_instruction(Opcode::LoadImmediate, dst, src);
                }
                break;

                case TokenKind::Register: {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::LoadRegister, dst, src);
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();
                    push_instruction(Opcode::LoadAddress, dst, src);
                }
                break;

                default:
                    break;
            }
        }
        break;

        case TokenKind::OpenBracket: {
            Operand dst = parse_address();
            expect(TokenKind::Comma);

            switch (look_ahead()->kind())
            {
                case TokenKind::Immediate: {
                    std::uint16_t src = parse_immediate();
                    push_instruction(Opcode::StoreImmediate, dst, src);
                }
                break;

                case TokenKind::Register: {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::StoreRegister, dst, src);
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();
                    push_instruction(Opcode::StoreAddress, dst, src);
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

void Parser::shl_instruction()
{
    expect(TokenKind::ShiftLeft);
    std::uint8_t dst = parse_register();
    expect(TokenKind::Comma);
    std::uint16_t src = parse_immediate();

    push_instruction(Opcode::ShiftLeft, dst, src);
}

void Parser::shr_instruction()
{
    expect(TokenKind::ShiftRight);
    std::uint8_t dst = parse_register();
    expect(TokenKind::Comma);
    std::uint16_t src = parse_immediate();

    push_instruction(Opcode::ShiftRight, dst, src);
}

void Parser::and_instruction()
{
    expect(TokenKind::BitAND);
    std::uint8_t dst = parse_register();
    expect(TokenKind::Comma);
    std::uint16_t src = parse_immediate();

    push_instruction(Opcode::BitwiseAND, dst, src);
}

void Parser::bor_instruction()
{
    expect(TokenKind::BitOR);
    std::uint8_t dst = parse_register();
    expect(TokenKind::Comma);
    std::uint16_t src = parse_immediate();

    push_instruction(Opcode::BitwiseOR, dst, src);
}

void Parser::xor_instruction()
{
    expect(TokenKind::BitXOR);
    std::uint8_t dst = parse_register();
    expect(TokenKind::Comma);
    std::uint16_t src = parse_immediate();

    push_instruction(Opcode::BitwiseXOR, dst, src);
}

void Parser::not_instruction()
{
    expect(TokenKind::BitNOT);
    std::uint8_t dst = parse_register();

    push_instruction(Opcode::BitwiseNOT, dst);
}

void Parser::psh_instruction()
{
    expect(TokenKind::Push);

    switch (look_ahead()->kind())
    {
        case TokenKind::Immediate: {
            std::uint16_t src = parse_immediate();
            push_instruction(Opcode::PushImmediate, src);
        }
        break;

        case TokenKind::Register: {
            std::uint8_t src = parse_register();
            push_instruction(Opcode::PushRegister, src);
        }
        break;

        case TokenKind::OpenBracket: {
            Operand src = parse_address();
            push_instruction(Opcode::PushAddress, src);
        }
        break;

        default:
            break;
    }
}

void Parser::pop_instruction()
{
    expect(TokenKind::Pop);
    std::uint8_t dst = parse_register();

    push_instruction(Opcode::Pop, dst);
}

void Parser::inc_instruction()
{
    expect(TokenKind::Increment);
    std::uint8_t dst = parse_register();

    push_instruction(Opcode::Increment, dst);
}

void Parser::dec_instruction()
{
    expect(TokenKind::Decrement);
    std::uint8_t dst = parse_register();

    push_instruction(Opcode::Decrement, dst);
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
                    push_instruction(Opcode::AddImmediate, dst, src);
                }
                break;

                case TokenKind::Register: {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::AddRegister, dst, src);
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();
                    push_instruction(Opcode::AddAddress, dst, src);
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
                    push_instruction(Opcode::SubImmediate, dst, src);
                }
                break;

                case TokenKind::Register: {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::SubRegister, dst, src);
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();
                    push_instruction(Opcode::SubAddress, dst, src);
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
                    push_instruction(Opcode::MulImmediate, dst, src);
                }
                break;

                case TokenKind::Register: {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::MulRegister, dst, src);
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();
                    push_instruction(Opcode::MulAddress, dst, src);
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
                    push_instruction(Opcode::DivImmediate, dst, src);
                }
                break;

                case TokenKind::Register: {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::DivRegister, dst, src);
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();
                    push_instruction(Opcode::DivAddress, dst, src);
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
                    push_instruction(Opcode::ModImmediate, dst, src);
                }
                break;

                case TokenKind::Register: {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::ModRegister, dst, src);
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();
                    push_instruction(Opcode::ModAddress, dst, src);
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
                    push_instruction(Opcode::CompareImmediate, dst, src);
                }
                break;

                case TokenKind::Register: {
                    auto src = parse_register();
                    push_instruction(Opcode::CompareRegister, dst, src);
                }
                break;

                case TokenKind::OpenBracket: {
                    Operand src = parse_address();
                    push_instruction(Opcode::CompareAddress, dst, src);
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
    Operand dst = parse_address();

    push_instruction(Opcode::Jump, dst);
}

void Parser::jeq_instruction()
{
    expect(TokenKind::JumpEquals);
    Operand dst = parse_address();

    push_instruction(Opcode::JumpEquals, dst);
}

void Parser::jne_instruction()
{
    expect(TokenKind::JumpNotEquals);
    Operand dst = parse_address();

    push_instruction(Opcode::JumpNotEquals, dst);
}

void Parser::jsr_instruction()
{
    expect(TokenKind::Subroutine);
    Operand dst = parse_address();

    push_instruction(Opcode::Subroutine, dst);
}

void Parser::ret_instruction()
{
    expect(TokenKind::Return);

    push_instruction(Opcode::Return);
}

void Parser::hlt_instruction()
{
    expect(TokenKind::Halt);

    push_instruction(Opcode::Halt);
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

    fmt::print("[Parser] Finished the parser, no errors reported.\n");

    m_asll->handle_instructions(m_instructions);
}

} // namespace Lunasm
