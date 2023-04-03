#pragma once

#include <memory>
#include <vector>
#include <optional>
#include <algorithm>
#include <filesystem>

#include "Lexer/Lexer.hpp"
#include "Lexer/Token.hpp"

namespace Lunasm {

class Parser
{
public:
    Parser();

    void Parse();

public:
    void parse_file(std::filesystem::path const&);

private:
    void step();
    Token current_token() const;
    std::optional<Token> look_ahead(std::size_t) const;

private:
    std::size_t m_index;
    std::vector<Token> m_tokens;
    std::unique_ptr<Lexer> m_lexer;
};

}  // namespace Lunasm
