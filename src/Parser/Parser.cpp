#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stdexcept>
#include <streambuf>

#include <fmt/core.h>

#include "Parser/Parser.hpp"
#include "Lexer/Mnemonics.hpp"

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

Token Parser::current_token() const
{
    return m_tokens.at(m_index);
}

std::optional<Token> Parser::look_ahead(std::size_t pos = 1) const
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
    if (current_token().kind() == kind)
    {
        step();
        return true;
    }
    else
    {
        auto err = fmt::format("[Parser] Invalid token kind expected: '{}' got '{}'\n", MNEMONICS.at(kind), current_token().as_string());
        throw std::runtime_error(err);
    }
}

void Parser::mov_instruction()
{
    switch (look_ahead()->kind())
    {
        case TokenKind::Register:
            expect(TokenKind::MovInstruction);
            expect(TokenKind::Register);
            expect(TokenKind::Comma);
            expect(TokenKind::Immediate);
            fmt::print("Parsed mov from immediate\n");
            break;

        default:
            fmt::print("Invalid mov instruction\n");
            std::exit(1);
            break;
    }
}

void Parser::Parse()
{
    while (current_token().kind() != TokenKind::END)
    {
        switch (current_token().kind())
        {
            case TokenKind::MovInstruction: mov_instruction(); break;

            default:
                fmt::print("[Parser] Unimplemented token kind: {}\n", current_token().as_string());
                step();
                break;
        }
    }
}

}  // namespace Lunasm
