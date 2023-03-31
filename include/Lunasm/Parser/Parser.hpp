#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <filesystem>

#include "Lexer/Lexer.hpp"
#include "Lexer/Token.hpp"

namespace Lunasm {

class Parser
{
public:
    Parser();
    Parser(std::vector<Token>);

    void parse_file(std::filesystem::path const&);

private:
    std::size_t m_index;
    std::unique_ptr<Lexer> m_lexer;
};

}  // namespace Lunasm
