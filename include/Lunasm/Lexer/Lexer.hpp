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
    void handle_space();
    bool is_empty() const;
    char current_char() const;
    std::optional<char> peek(std::size_t) const;
    std::string sanitize_input(std::string);

private:
    void lex_comments();

    Token lex_directives();
    Token lex_separators();
    Token lex_operators();
    Token lex_registers();
    Token lex_instructions();

    std::uint16_t get_base();
    Token lex_immediates();

    Token next_token();

private:
    std::size_t m_line;
    std::size_t m_index;
    std::string m_source_code;
};

} // namespace Lexer
