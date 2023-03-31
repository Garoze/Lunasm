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

Parser::Parser(std::vector<Token> token)
    : m_index(0)
    , m_lexer(new Lexer())
{}

void Parser::tokens(std::vector<Token> tokens)
{
    m_tokens = std::move(tokens);
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

    auto tokens = m_lexer->lex_source(source);

    for (const auto& t : tokens)
    {
        t.print();
    }
}

}  // namespace Lunasm
