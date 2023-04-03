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

Token Parser::look_ahead()
{
    return m_tokens.at(m_index);
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

    auto tokens = m_lexer->Lex_source(source);

    for (const auto& t : tokens)
    {
        t.print();
    }
}

}  // namespace Lunasm
