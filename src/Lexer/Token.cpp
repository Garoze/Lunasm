#include <string>
#include <type_traits>
#include <variant>

#include "fmt/core.h"

#include "Lexer/Kind.hpp"
#include "Lexer/Token.hpp"

namespace Lunasm {

Token::Token(Kind kind, TokenValue value, std::size_t line, std::size_t offset)
    : m_kind(Kind(kind))
    , m_line(line)
    , m_value(value)
    , m_offset(offset)
{}

void Token::print() const
{
    fmt::print("Token\n");
    // auto text = fmt::format("\"{text}\"");
    // auto kind = fmt::format("<{}>", m_kind.as_string());
    //
    // fmt::print("Token( Kind: {:18} Text: {:10} Line: {:2d} Offset: {:2d} )\n", kind, text, m_line, m_offset);
}

TokenKind Token::kind() const
{
    return m_kind.raw();
}

TokenValue Token::value() const
{
    return m_value;
}

std::string Token::as_string() const
{
    return m_kind.as_string();
}

}  // namespace Lunasm
