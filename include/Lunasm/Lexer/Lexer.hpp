#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "Token.hpp"

namespace Lexer {

class Lexer
{
public:
    Lexer();
    Lexer(const std::string&);

    std::vector<Token> Tokenizer();
    std::vector<Token> Lex_source(std::string);

    std::vector<Token> Lex_file(std::filesystem::path const&, bool);

private:
    void step();
    void space();

    char current_char() const;

private:
    bool is_empty() const;
    std::optional<char> peek(std::size_t) const;

private:
    std::string sanitize_input(std::string);

private:
    void lex_comments();
    Token lex_registers();
    Token lex_immediates();
    Token lex_instructions();

    Token lex_operators();
    Token lex_separators();

    std::uint16_t get_base();

private:
    Token next_token();

private:
    bool m_debug;
    std::size_t m_line;
    std::size_t m_index;
    std::string m_source_code;
};

} // namespace Lexer
