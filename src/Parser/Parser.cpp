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

#include "Parser/ASL.hpp"
#include "Parser/Instruction.hpp"
#include "Parser/Label.hpp"
#include "Parser/Opcodes.hpp"
#include "Parser/Parser.hpp"
#include "Parser/Sizes.hpp"

namespace Parser {

Parser::Parser()
    : m_index(0)
    , m_lexer(std::make_unique<Lexer::Lexer>())
    , m_asll(std::make_unique<ASL>())
{}

void Parser::step()
{
    if ((m_index + 1) < m_tokens.size())
    {
        m_index++;
    }
}

std::optional<Lexer::Token> Parser::look_ahead(std::size_t pos = 0)
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

    m_tokens = m_lexer->Lex_source(source);

    Parse();
}

Lexer::Token Parser::expect(Lexer::Kind::kind_t kind)
{
    auto t = look_ahead();
    if (t.has_value() && t->kind().raw() == kind)
    {
        step();
        return t.value();
    }
    else
    {
        auto err =
            fmt::format("[Parser] Invalid token kind expected: '{}' got '{}'\n",
                        Lexer::KIND_TO_STR.at(kind), look_ahead()->as_string());

        throw std::runtime_error(err);
    }
}

template <typename... Kinds>
std::optional<Lexer::Token> Parser::expect_any(Kinds... kinds)
{
    static_assert((std::is_same_v<Kinds, Lexer::Kind::kind_t> && ...),
                  "must pass Lexer::Kind::kind_t values");

    auto t = look_ahead();
    if (t.has_value())
    {
        for (Lexer::Kind::kind_t k : { kinds... })
        {
            if (t->kind().raw() == k)
            {
                step();
                return t.value();
            }
        }
    }

    return {};
}

uint16_t Parser::parse_register()
{
    auto r = expect(Lexer::Kind::kind_t::Register);

    return std::get<std::uint16_t>(r.value().raw());
}

std::uint16_t Parser::parse_immediate()
{
    auto i = expect(Lexer::Kind::kind_t::Immediate);

    return std::get<std::uint16_t>(i.value().raw());
}

std::string_view Parser::parse_label()
{
    auto l = expect(Lexer::Kind::kind_t::Symbol);
    expect(Lexer::Kind::kind_t::Colon);

    auto identifier = std::get<std::string_view>(l.value().raw());

    m_instructions.push_back(Label(identifier));

    // fmt::print("[Parser] Label definition: `{}`\n", identifier);

    return identifier;
}

Operand Parser::parse_address()
{
    expect(Lexer::Kind::kind_t::OpenSquare);

    auto a =
        expect_any(Lexer::Kind::kind_t::Immediate,
                   Lexer::Kind::kind_t::Register, Lexer::Kind::kind_t::Symbol);

    expect(Lexer::Kind::kind_t::CloseSquare);

    return std::get<std::string_view>(a->value().raw());
}

void Parser::push_instruction(Opcode op, Operand dst = {}, Operand src = {})
{
    m_instructions.push_back(Instruction{ op, INST_SIZE.at(op), dst, src });
}

void Parser::nop_instruction()
{
    expect(Lexer::Kind::kind_t::Nop);
    push_instruction(Opcode::NOP);
}

void Parser::mov_instruction()
{
    expect(Lexer::Kind::kind_t::Mov);

    switch (look_ahead()->kind().raw())
    {
        case Lexer::Kind::kind_t::Register:
        {
            std::uint8_t dst = parse_register();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    std::uint16_t src = parse_immediate();
                    push_instruction(Opcode::LoadImmediate, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::LoadRegister, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
                    Operand src = parse_address();
                    push_instruction(Opcode::LoadAddress, dst, src);
                }
                break;

                default:
                    break;
            }
        }
        break;

        case Lexer::Kind::kind_t::OpenSquare:
        {
            Operand dst = parse_address();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    std::uint16_t src = parse_immediate();
                    push_instruction(Opcode::StoreImmediate, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::StoreRegister, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
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
    expect(Lexer::Kind::kind_t::ShiftLeft);
    std::uint8_t dst = parse_register();
    expect(Lexer::Kind::kind_t::Comma);
    std::uint16_t src = parse_immediate();

    push_instruction(Opcode::ShiftLeft, dst, src);
}

void Parser::shr_instruction()
{
    expect(Lexer::Kind::kind_t::ShiftRight);
    std::uint8_t dst = parse_register();
    expect(Lexer::Kind::kind_t::Comma);
    std::uint16_t src = parse_immediate();

    push_instruction(Opcode::ShiftRight, dst, src);
}

void Parser::and_instruction()
{
    expect(Lexer::Kind::kind_t::And);
    std::uint8_t dst = parse_register();
    expect(Lexer::Kind::kind_t::Comma);
    std::uint16_t src = parse_immediate();

    push_instruction(Opcode::BitwiseAND, dst, src);
}

void Parser::bor_instruction()
{
    expect(Lexer::Kind::kind_t::Or);
    std::uint8_t dst = parse_register();
    expect(Lexer::Kind::kind_t::Comma);
    std::uint16_t src = parse_immediate();

    push_instruction(Opcode::BitwiseOR, dst, src);
}

void Parser::xor_instruction()
{
    expect(Lexer::Kind::kind_t::Xor);
    std::uint8_t dst = parse_register();
    expect(Lexer::Kind::kind_t::Comma);
    std::uint16_t src = parse_immediate();

    push_instruction(Opcode::BitwiseXOR, dst, src);
}

void Parser::not_instruction()
{
    expect(Lexer::Kind::kind_t::Not);
    std::uint8_t dst = parse_register();

    push_instruction(Opcode::BitwiseNOT, dst);
}

void Parser::psh_instruction()
{
    expect(Lexer::Kind::kind_t::Push);

    switch (look_ahead()->kind().raw())
    {
        case Lexer::Kind::kind_t::Immediate:
        {
            std::uint16_t src = parse_immediate();
            push_instruction(Opcode::PushImmediate, src);
        }
        break;

        case Lexer::Kind::kind_t::Register:
        {
            std::uint8_t src = parse_register();
            push_instruction(Opcode::PushRegister, src);
        }
        break;

        case Lexer::Kind::kind_t::OpenSquare:
        {
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
    expect(Lexer::Kind::kind_t::Pop);
    std::uint8_t dst = parse_register();

    push_instruction(Opcode::Pop, dst);
}

void Parser::inc_instruction()
{
    expect(Lexer::Kind::kind_t::Increment);
    std::uint8_t dst = parse_register();

    push_instruction(Opcode::Increment, dst);
}

void Parser::dec_instruction()
{
    expect(Lexer::Kind::kind_t::Decrement);
    std::uint8_t dst = parse_register();

    push_instruction(Opcode::Decrement, dst);
}

void Parser::add_instruction()
{
    expect(Lexer::Kind::kind_t::Add);

    switch (look_ahead()->kind().raw())
    {
        case Lexer::Kind::kind_t::Register:
        {
            std::uint8_t dst = parse_register();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    std::uint16_t src = parse_immediate();
                    push_instruction(Opcode::AddImmediate, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::AddRegister, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
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
    expect(Lexer::Kind::kind_t::Sub);

    switch (look_ahead()->kind().raw())
    {
        case Lexer::Kind::kind_t::Register:
        {
            std::uint8_t dst = parse_register();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    std::uint16_t src = parse_immediate();
                    push_instruction(Opcode::SubImmediate, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::SubRegister, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
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
    expect(Lexer::Kind::kind_t::Mul);

    switch (look_ahead()->kind().raw())
    {
        case Lexer::Kind::kind_t::Register:
        {
            std::uint8_t dst = parse_register();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    std::uint16_t src = parse_immediate();
                    push_instruction(Opcode::MulImmediate, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::MulRegister, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
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
    expect(Lexer::Kind::kind_t::Div);

    switch (look_ahead()->kind().raw())
    {
        case Lexer::Kind::kind_t::Register:
        {
            std::uint8_t dst = parse_register();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    std::uint16_t src = parse_immediate();
                    push_instruction(Opcode::DivImmediate, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::DivRegister, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
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
    expect(Lexer::Kind::kind_t::Mod);

    switch (look_ahead()->kind().raw())
    {
        case Lexer::Kind::kind_t::Register:
        {
            std::uint8_t dst = parse_register();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    std::uint16_t src = parse_immediate();
                    push_instruction(Opcode::ModImmediate, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    std::uint8_t src = parse_register();
                    push_instruction(Opcode::ModRegister, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
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
    expect(Lexer::Kind::kind_t::Compare);

    switch (look_ahead()->kind().raw())
    {
        case Lexer::Kind::kind_t::Register:
        {
            std::uint8_t dst = parse_register();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    std::uint16_t src = parse_immediate();
                    push_instruction(Opcode::CompareImmediate, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    auto src = parse_register();
                    push_instruction(Opcode::CompareRegister, dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
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
    expect(Lexer::Kind::kind_t::Jump);
    Operand dst = parse_address();

    push_instruction(Opcode::Jump, dst);
}

void Parser::jeq_instruction()
{
    expect(Lexer::Kind::kind_t::JumpIfEquals);
    Operand dst = parse_address();

    push_instruction(Opcode::JumpEquals, dst);
}

void Parser::jne_instruction()
{
    expect(Lexer::Kind::kind_t::JumpIfNotEquals);
    Operand dst = parse_address();

    push_instruction(Opcode::JumpNotEquals, dst);
}

void Parser::jsr_instruction()
{
    expect(Lexer::Kind::kind_t::Subroutine);
    Operand dst = parse_address();

    push_instruction(Opcode::Subroutine, dst);
}

void Parser::ret_instruction()
{
    expect(Lexer::Kind::kind_t::Return);

    push_instruction(Opcode::Return);
}

void Parser::hlt_instruction()
{
    expect(Lexer::Kind::kind_t::Halt);

    push_instruction(Opcode::Halt);
}

void Parser::Parse()
{
    while (look_ahead()->kind().raw() != Lexer::Kind::kind_t::__EOF)
    {
        switch (look_ahead()->kind().raw())
        {
            case Lexer::Kind::kind_t::Symbol:
                parse_label();
                break;

            case Lexer::Kind::kind_t::Nop:
                nop_instruction();
                break;

            case Lexer::Kind::kind_t::Mov:
                mov_instruction();
                break;

            case Lexer::Kind::kind_t::ShiftLeft:
                shl_instruction();
                break;

            case Lexer::Kind::kind_t::ShiftRight:
                shr_instruction();
                break;

            case Lexer::Kind::kind_t::And:
                and_instruction();
                break;

            case Lexer::Kind::kind_t::Or:
                bor_instruction();
                break;

            case Lexer::Kind::kind_t::Xor:
                xor_instruction();
                break;

            case Lexer::Kind::kind_t::Not:
                not_instruction();
                break;

            case Lexer::Kind::kind_t::Push:
                psh_instruction();
                break;

            case Lexer::Kind::kind_t::Pop:
                pop_instruction();
                break;

            case Lexer::Kind::kind_t::Increment:
                inc_instruction();
                break;

            case Lexer::Kind::kind_t::Decrement:
                dec_instruction();
                break;

            case Lexer::Kind::kind_t::Add:
                add_instruction();
                break;

            case Lexer::Kind::kind_t::Sub:
                sub_instruction();
                break;

            case Lexer::Kind::kind_t::Mul:
                mul_instruction();
                break;

            case Lexer::Kind::kind_t::Div:
                div_instruction();
                break;

            case Lexer::Kind::kind_t::Mod:
                mod_instruction();
                break;

            case Lexer::Kind::kind_t::Compare:
                cmp_instruction();
                break;

            case Lexer::Kind::kind_t::Jump:
                jmp_instruction();
                break;

            case Lexer::Kind::kind_t::JumpIfEquals:
                jeq_instruction();
                break;

            case Lexer::Kind::kind_t::JumpIfNotEquals:
                jne_instruction();
                break;

            case Lexer::Kind::kind_t::Subroutine:
                jsr_instruction();
                break;

            case Lexer::Kind::kind_t::Return:
                ret_instruction();
                break;

            case Lexer::Kind::kind_t::Halt:
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

} // namespace Parser
