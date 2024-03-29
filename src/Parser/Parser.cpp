#include <algorithm>
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

#include "Lexer/Forward.hpp"
#include "Parser/Forward.hpp"

namespace Parser {

Parser::Parser()
    : m_index(0)
    , m_lexer(std::make_unique<Lexer::Lexer>())
{}

void Parser::step()
{
    if ((m_index + 1) <= m_tokens.size())
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

// void Parser::parse_file(std::filesystem::path const& path, bool debug)
std::vector<std::unique_ptr<Instruction>>&
Parser::parse_file(std::filesystem::path const& path, bool debug)
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

    return m_instructions;
}

Lexer::Token Parser::expect(Lexer::Kind::kind_t kind)
{
    auto token = look_ahead();
    if (token.has_value() && token->kind().raw() == kind)
    {
        step();
        return token.value();
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

template <typename T, typename... Args>
void Parser::push_instruction(Args&&... args)
{
    m_instructions.push_back(
        std::move(std::make_unique<T>(std::forward<Args>(args)...)));
}

bool Parser::match(Lexer::Kind::kind_t kind)
{
    return look_ahead()->kind().raw() == kind;
}

std::string_view Parser::parse_label()
{
    auto token = expect(Lexer::Kind::kind_t::Symbol);

    expect_any(Lexer::Kind::kind_t::Colon, Lexer::Kind::kind_t::CloseSquare);

    auto symbol = std::get<std::string_view>(token.value().raw());

    push_instruction<Label>(symbol);

    return symbol;
}

void Parser::nop_instruction()
{
    expect(Lexer::Kind::kind_t::Nop);
    push_instruction<Nop>();
}

std::optional<Operand::value_t> Parser::parse_operand()
{
    switch (look_ahead()->kind().raw())
    {
        case Lexer::Kind::kind_t::Register:
        {
            return std::get<std::uint16_t>(
                expect(Lexer::Kind::kind_t::Register).value().raw());
        }
        break;

        case Lexer::Kind::kind_t::Immediate:
        {
            return std::get<std::uint16_t>(
                expect(Lexer::Kind::kind_t::Immediate).value().raw());
        }
        break;

        case Lexer::Kind::kind_t::OpenSquare:
        {
            expect(Lexer::Kind::kind_t::OpenSquare);

            auto token = expect(Lexer::Kind::kind_t::Symbol);

            expect(Lexer::Kind::kind_t::CloseSquare);

            return std::get<std::string_view>(token.value().raw());
        }
        break;

        default:
            break;
    }

    return {};
}

void Parser::mov_instruction()
{
    expect(Lexer::Kind::kind_t::Mov);

    switch (look_ahead()->kind().raw())
    {
        case Lexer::Kind::kind_t::Register:
        {
            auto dst = parse_operand().value();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    auto src = parse_operand().value();
                    push_instruction<LoadImmediate>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    auto src = parse_operand().value();
                    push_instruction<LoadRegister>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
                    auto src = parse_operand().value();
                    push_instruction<LoadAddress>(dst, src);
                }
                break;

                default:
                    break;
            }
        }
        break;

        case Lexer::Kind::kind_t::OpenSquare:
        {
            auto dst = parse_operand().value();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    auto src = parse_operand().value();
                    push_instruction<StoreImmediate>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    auto src = parse_operand().value();
                    push_instruction<StoreRegister>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
                    auto src = parse_operand().value();
                    push_instruction<StoreAddress>(dst, src);
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
    auto dst = parse_operand().value();
    expect(Lexer::Kind::kind_t::Comma);
    auto src = parse_operand().value();

    push_instruction<ShiftLeft>(dst, src);
}

void Parser::shr_instruction()
{
    expect(Lexer::Kind::kind_t::ShiftRight);
    auto dst = parse_operand().value();
    expect(Lexer::Kind::kind_t::Comma);
    auto src = parse_operand().value();

    push_instruction<ShiftRight>(dst, src);
}

void Parser::and_instruction()
{
    expect(Lexer::Kind::kind_t::And);
    auto dst = parse_operand().value();
    expect(Lexer::Kind::kind_t::Comma);
    auto src = parse_operand().value();

    push_instruction<And>(dst, src);
}

void Parser::bor_instruction()
{
    expect(Lexer::Kind::kind_t::Or);
    auto dst = parse_operand().value();
    expect(Lexer::Kind::kind_t::Comma);
    auto src = parse_operand().value();

    push_instruction<Or>(dst, src);
}

void Parser::xor_instruction()
{
    expect(Lexer::Kind::kind_t::Xor);
    auto dst = parse_operand().value();
    expect(Lexer::Kind::kind_t::Comma);
    auto src = parse_operand().value();

    push_instruction<Xor>(dst, src);
}

void Parser::not_instruction()
{
    expect(Lexer::Kind::kind_t::Not);
    auto dst = parse_operand().value();

    push_instruction<Not>(dst);
}

void Parser::psh_instruction()
{
    expect(Lexer::Kind::kind_t::Push);

    switch (look_ahead()->kind().raw())
    {
        case Lexer::Kind::kind_t::Immediate:
        {
            auto src = parse_operand().value();
            push_instruction<PushImmediate>(src);
        }
        break;

        case Lexer::Kind::kind_t::Register:
        {
            auto src = parse_operand().value();
            push_instruction<PushRegister>(src);
        }
        break;

        case Lexer::Kind::kind_t::OpenSquare:
        {
            auto src = parse_operand().value();
            push_instruction<PushAddress>(src);
        }
        break;

        default:
            break;
    }
}

void Parser::pop_instruction()
{
    expect(Lexer::Kind::kind_t::Pop);
    auto dst = parse_operand().value();

    push_instruction<Pop>(dst);
}

void Parser::inc_instruction()
{
    expect(Lexer::Kind::kind_t::Increment);
    auto dst = parse_operand().value();

    push_instruction<Increment>(dst);
}

void Parser::dec_instruction()
{
    expect(Lexer::Kind::kind_t::Decrement);
    auto dst = parse_operand().value();

    push_instruction<Decrement>(dst);
}

void Parser::add_instruction()
{
    expect(Lexer::Kind::kind_t::Add);

    switch (look_ahead()->kind().raw())
    {
        case Lexer::Kind::kind_t::Register:
        {
            auto dst = parse_operand().value();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    auto src = parse_operand().value();
                    push_instruction<AddImmediate>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    auto src = parse_operand().value();
                    push_instruction<AddRegister>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
                    auto src = parse_operand().value();
                    push_instruction<AddAddress>(dst, src);
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
            auto dst = parse_operand().value();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    auto src = parse_operand().value();
                    push_instruction<SubImmediate>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    auto src = parse_operand().value();
                    push_instruction<SubRegister>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
                    auto src = parse_operand().value();
                    push_instruction<SubAddress>(dst, src);
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
            auto dst = parse_operand().value();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    auto src = parse_operand().value();
                    push_instruction<MulImmediate>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    auto src = parse_operand().value();
                    push_instruction<MulRegister>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
                    auto src = parse_operand().value();
                    push_instruction<MulAddress>(dst, src);
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
            auto dst = parse_operand().value();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    auto src = parse_operand().value();
                    push_instruction<DivImmediate>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    auto src = parse_operand().value();
                    push_instruction<DivRegister>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
                    auto src = parse_operand().value();
                    push_instruction<DivAddress>(dst, src);
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
            auto dst = parse_operand().value();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    auto src = parse_operand().value();
                    push_instruction<ModImmediate>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    auto src = parse_operand().value();
                    push_instruction<ModRegister>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
                    auto src = parse_operand().value();
                    push_instruction<ModAddress>(dst, src);
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
            auto dst = parse_operand().value();
            expect(Lexer::Kind::kind_t::Comma);

            switch (look_ahead()->kind().raw())
            {
                case Lexer::Kind::kind_t::Immediate:
                {
                    auto src = parse_operand().value();
                    push_instruction<CompareImmediate>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::Register:
                {
                    auto src = parse_operand().value();
                    push_instruction<CompareRegister>(dst, src);
                }
                break;

                case Lexer::Kind::kind_t::OpenSquare:
                {
                    auto src = parse_operand().value();
                    push_instruction<CompareAddress>(dst, src);
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
    auto dst = parse_operand().value();

    push_instruction<Jump>(dst);
}

void Parser::jeq_instruction()
{
    expect(Lexer::Kind::kind_t::JumpIfEquals);
    auto dst = parse_operand().value();

    push_instruction<JumpIfEquals>(dst);
}

void Parser::jne_instruction()
{
    expect(Lexer::Kind::kind_t::JumpIfNotEquals);
    auto dst = parse_operand().value();

    push_instruction<JumpIfNotEquals>(dst);
}

void Parser::jsr_instruction()
{
    expect(Lexer::Kind::kind_t::Subroutine);
    auto dst = parse_operand().value();

    push_instruction<Subroutine>(dst);
}

void Parser::ret_instruction()
{
    expect(Lexer::Kind::kind_t::Return);

    push_instruction<Return>();
}

void Parser::hlt_instruction()
{
    expect(Lexer::Kind::kind_t::Halt);

    push_instruction<Halt>();
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
}

} // namespace Parser
