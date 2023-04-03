#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <streambuf>
#include <algorithm>
#include <stdexcept>

#include <fmt/core.h>

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

void Parser::Parse()
{
    while (current_token().kind() != TokenKind::END)
    {
        switch (current_token().kind())
        {
            default:
                fmt::print("[Parser] Unimplemented token kind: {}\n", current_token().as_string());
                step();
                break;
        }
    }
}

}  // namespace Lunasm
