#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <streambuf>
#include <algorithm>
#include <stdexcept>

#include "Parser/Parser.hpp"
#include "fmt/core.h"

namespace Lunasm {

Parser::Parser()
    : m_index(0)
{}

Parser::Parser(std::vector<Token> token)
    : m_index(0)
{}

void Parser::tokens(std::vector<Token> tokens)
{
    m_tokens = std::move(tokens);
}

void Parser::parse_file(std::filesystem::path const& path)
{
    const std::ifstream file(path, std::ios::in);

    if (!file.good())
    {
        auto err = fmt::format("Could not open the file {}", path.string());
        throw std::runtime_error(err);
    }

    std::stringstream ss;

    ss << file.rdbuf();

    std::string source = ss.str();

    fmt::print("Code: {}\n", source);
}

}  // namespace Lunasm
