#include <memory>
#include <string>
#include <sstream>
#include <cstdint>
#include <fstream>
#include <charconv>
#include <iterator>
#include <stdexcept>
#include <streambuf>
#include <initializer_list>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include "Lexer/Mnemonics.hpp"

#include "Parser/Instruction.hpp"
#include "Parser/Parser.hpp"
#include "Parser/Opcodes.hpp"

namespace Lunasm {

Parser::Parser()
    : m_index(0)
    , m_lexer(std::make_unique<Lexer>())
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
        auto err = fmt::format("[Parser] Invalid token kind expected: '{}' got '{}'\n", MNEMONICS.at(kind), look_ahead()->as_string());
        throw std::runtime_error(err);
    }
}

template <typename... Kinds>
std::optional<Token> Parser::expect_any(Kinds... kinds)
{
    static_assert((std::is_same_v<Kinds, TokenKind> && ...), "must pass TokenKind values");

    for (TokenKind k : { kinds... })
    {
        if (look_ahead()->kind() == k)
        {
            return expect(k);
        }
    }

    return {};
}

bool Parser::parse_label()
{
    auto label = expect(TokenKind::Label);
    expect(TokenKind::Colon);

    auto identifier = std::get<std::string_view>(label.raw_value());

    // fmt::print("[LABEL `{}`]: 0x{:04X}\n", identifier, m_asll->index());

    return true;
}

uint8_t Parser::parse_register()
{
    auto r = expect(TokenKind::Register);

    return std::get<std::uint8_t>(r.raw_value());
}

std::uint16_t Parser::parse_address()
{
    expect(TokenKind::OpenBracket);
    expect_any(TokenKind::Immediate, TokenKind::Register, TokenKind::Label);
    expect(TokenKind::CloseBracket);

    return false;
}

std::uint16_t Parser::parse_immediate()
{
    auto i = expect(TokenKind::Immediate);

    return std::get<std::uint16_t>(i.raw_value());
}

void Parser::parse_modes()
{
    switch (look_ahead()->kind())
    {
        case TokenKind::Immediate:
            parse_immediate();
            break;
        case TokenKind::Register:
            parse_register();
            break;
        case TokenKind::OpenBracket:
            parse_address();
            break;

        default:
            break;
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

                    m_instructions.push_back(Instruction(Opcode::LoadImmediate, 4, dst, src));
                }
                break;

                case TokenKind::Register: {
                    auto src = parse_register();

                    m_instructions.push_back(Instruction(Opcode::LoadRegister, 3, dst, src));
                }
                break;

                case TokenKind::OpenBracket: {
                    auto src = parse_address();

                    m_instructions.push_back(Instruction(Opcode::LoadAddress, 4, dst, src));
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
            parse_modes();
            break;

        default:
            break;
    }
}

void Parser::shl_instruction()
{
    expect(TokenKind::ShiftLeft);
    parse_register();
    expect(TokenKind::Comma);
    parse_immediate();
}

void Parser::shr_instruction()
{
    expect(TokenKind::ShiftRight);
    parse_register();
    expect(TokenKind::Comma);
    parse_immediate();
}

void Parser::and_instruction()
{
    expect(TokenKind::BitAND);
    parse_register();
    expect(TokenKind::Comma);
    parse_immediate();
}

void Parser::bor_instruction()
{
    expect(TokenKind::BitOR);
    parse_register();
    expect(TokenKind::Comma);
    parse_immediate();
}

void Parser::xor_instruction()
{
    expect(TokenKind::BitXOR);
    parse_register();
    expect(TokenKind::Comma);
    parse_immediate();
}

void Parser::not_instruction()
{
    expect(TokenKind::BitNOT);
    parse_register();
}

void Parser::psh_instruction()
{
    expect(TokenKind::Push);
    parse_modes();
}

void Parser::pop_instruction()
{
    expect(TokenKind::Pop);
    parse_register();
}

void Parser::inc_instruction()
{
    expect(TokenKind::Increment);
    parse_register();
}

void Parser::dec_instruction()
{
    expect(TokenKind::Decrement);
    parse_register();
}

void Parser::add_instruction()
{
    expect(TokenKind::Add);
    parse_register();
    expect(TokenKind::Comma);
    parse_modes();
}

void Parser::sub_instruction()
{
    expect(TokenKind::Sub);
    parse_register();
    expect(TokenKind::Comma);
    parse_modes();
}

void Parser::mul_instruction()
{
    expect(TokenKind::Mul);
    parse_register();
    expect(TokenKind::Comma);
    parse_modes();
}

void Parser::div_instruction()
{
    expect(TokenKind::Div);
    parse_register();
    expect(TokenKind::Comma);
    parse_modes();
}

void Parser::mod_instruction()
{
    expect(TokenKind::Mod);
    parse_register();
    expect(TokenKind::Comma);
    parse_modes();
}

void Parser::cmp_instruction()
{
    expect(TokenKind::Compare);
    parse_register();
    expect(TokenKind::Comma);
    parse_modes();
}

void Parser::jmp_instruction()
{
    expect(TokenKind::Jump);
    parse_address();
}

void Parser::jeq_instruction()
{
    expect(TokenKind::JumpEquals);
    parse_address();
}

void Parser::jne_instruction()
{
    expect(TokenKind::JumpNotEquals);
    parse_address();
}

void Parser::jsr_instruction()
{
    expect(TokenKind::Subroutine);
    parse_address();
}

void Parser::ret_instruction()
{
    expect(TokenKind::Return);
}

void Parser::hlt_instruction()
{
    expect(TokenKind::Halt);
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
                fmt::print("[Parser] Unimplemented token kind: {}\n", look_ahead()->as_string());
                step();
                break;
        }
    }

    debug_instruction();
    fmt::print("[Parser] Finished the parser, no errors reported.\n");
}

void Parser::debug_instruction() const
{
    for (auto i : m_instructions)
    {
        i.print();
    }
}

}  // namespace Lunasm
