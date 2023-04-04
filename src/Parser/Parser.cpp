#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>

#include <fmt/core.h>

#include "Lexer/Mnemonics.hpp"
#include "Parser/Parser.hpp"

namespace Lunasm {

Parser::Parser()
    : m_index(0)
    , m_lexer(new Lexer())
{}

void Parser::step()
{
    if ((m_index + 1) < m_tokens.size())
    {
        m_index++;
    }
}

void Parser::skip(const std::string& message)
{
#ifdef __PARSER_DEBUG__
    fmt::print("DEBUG: {}\n", message);
#endif
    step();
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

void Parser::parse_file(std::filesystem::path const& path)
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

bool Parser::expect(TokenKind kind)
{
    if (look_ahead()->kind() == kind)
    {
        step();
        return true;
    }
    else
    {
        auto err = fmt::format("[Parser] Invalid token kind expected: '{}' got '{}'\n", MNEMONICS.at(kind), look_ahead()->as_string());
        throw std::runtime_error(err);
    }
}

bool Parser::parse_immediate()
{
    expect(TokenKind::Immediate);

    return true;
}

bool Parser::parse_address()
{
    expect(TokenKind::OpenBracket);
    parse_immediate();
    expect(TokenKind::CloseBracket);

    return true;
}

bool Parser::parse_register()
{
    expect(TokenKind::Register);

    return true;
}

void Parser::mov_instruction()
{
    expect(TokenKind::MovInstruction);

    switch (look_ahead()->kind())
    {
        case TokenKind::Register:
            parse_register();
            expect(TokenKind::Comma);
            switch (look_ahead()->kind())
            {
                case TokenKind::Immediate:
                    parse_immediate();
                    fmt::print("Load from Immediate\n");
                    break;
                case TokenKind::Register:
                    parse_register();
                    fmt::print("Load from Register\n");
                    break;
                case TokenKind::OpenBracket:
                    parse_address();
                    fmt::print("Load from Address\n");
                    break;

                default:
                    break;
            }
            break;
        case TokenKind::OpenBracket:
            parse_address();
            expect(TokenKind::Comma);
            switch (look_ahead()->kind())
            {
                case TokenKind::Immediate:
                    parse_immediate();
                    fmt::print("Store from Immediate\n");
                    break;
                case TokenKind::Register:
                    parse_register();
                    fmt::print("Store from Register\n");
                    break;
                case TokenKind::OpenBracket:
                    parse_address();
                    fmt::print("Store from Address\n");
                    break;

                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Parser::Parse()
{
    while (look_ahead()->kind() != TokenKind::END)
    {
        switch (look_ahead()->kind())
        {
            case TokenKind::MovInstruction:
                mov_instruction();
                break;

            default:
                fmt::print("[Parser] Unimplemented token kind: {}\n", look_ahead()->as_string());
                step();
                break;
        }
    }
}

}  // namespace Lunasm
