#pragma once

#include <string>
#include <vector>
#include <optional>
#include <string_view>

#include "Token.hpp"

namespace Lunasm {

class Lexer
{
public:
    Lexer();
    Lexer(const std::string&);

    std::vector<Token> Tokenizer();
    std::vector<Token> Lex_source(std::string);

    void enable_debug(bool);

private:
    char eat();
    void step();
    void space();
    void skip(std::size_t);
    void skip(const std::string&);

    char current_char() const;

private:
    bool is_empty() const;
    std::size_t offset(std::size_t) const;
    std::optional<char> peek(std::size_t) const;

private:
    std::string sanitize_input(std::string);

private:
    void Comment();
    Token Register();
    Token Immediate();
    Token Identifier();


private:
    Token next_token();

private:
    bool m_debug;
    std::size_t m_line;
    std::size_t m_index;
    std::string m_source_code;
};

}  // namespace Lunasm
