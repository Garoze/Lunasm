#pragma once

#include <vector>
#include <filesystem>

#include "Lexer/Token.hpp"

namespace Lunasm {

class Parser
{
public:
    Parser();
    Parser(std::vector<Token>);

    void parse_file(std::filesystem::path const&);

    void tokens(std::vector<Token>);

private:
    std::size_t m_index;
    std::vector<Token> m_tokens;
};

}  // namespace Lunasm
