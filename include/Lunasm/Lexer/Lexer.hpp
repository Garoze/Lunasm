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
    Lexer(const std::string&);

    std::vector<Token> Tokenizer();

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
    Token Register();
    Token Immediate();
    Token Identifier();

private:
    Token next_token();

private:
    std::size_t m_line;
    std::size_t m_index;
    std::string m_source_code;
};

}  // namespace Lunasm
