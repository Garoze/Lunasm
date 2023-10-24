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

    std::optional<char> peek(std::size_t) const;
    std::string sanitize_input(std::string);

    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] char current_char() const;

private:
    void lex_comments();
    std::uint16_t get_base();

    [[nodiscard]] Token lex_directives();
    [[nodiscard]] Token lex_separators();
    [[nodiscard]] Token lex_operators();
    [[nodiscard]] Token lex_registers();
    [[nodiscard]] Token lex_instructions();
    [[nodiscard]] Token lex_immediates();

    [[nodiscard]] Token next_token();

private:
    std::size_t m_line;
    std::size_t m_index;
    std::string m_source_code;
};

} // namespace Lexer
