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
    void parse_file(std::filesystem::path const&);

private:
    void step();
    void skip(const std::string&);
    std::optional<Token> look_ahead(std::size_t);

private:
    bool parse_immediate();
    bool parse_address();
    bool parse_register();

private:
    void mov_instruction();

private:
    bool expect(TokenKind);
    bool expect_any(TokenKind, TokenKind);

private:
    std::size_t m_index;
    std::vector<Token> m_tokens;
    std::unique_ptr<Lexer> m_lexer;
};

}  // namespace Lunasm
