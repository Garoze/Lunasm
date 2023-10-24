#include <string>
#include <type_traits>
#include <variant>

#include "fmt/core.h"

#include "Lexer/Kind.hpp"
#include "Lexer/Token.hpp"

namespace Lexer {

Token::Token(Kind::kind_t kind, Value::value_t value, std::string file,
             std::size_t line, std::size_t column)
    : m_kind(kind)
    , m_value(value)
    , m_location(file, line, column)
{}

const Kind& Token::kind() const
{
    return m_kind;
}

const Value& Token::value() const
{
    return m_value;
}

const Location& Token::location() const
{
    return m_location;
}

std::string Token::as_string() const
{
    auto kind = fmt::format("<{}>", m_kind.as_string());

    auto value = fmt::format(
        "\"{}\"", (m_kind.raw() == Kind::kind_t::Register ? "r" : "") +
                      m_value.as_string());

    return fmt::format(
        "Token( Kind: {:18} Text: {:10} Line: {:2d} Column: {:2d})\n", kind,
        value, m_location.line(), m_location.column());
}

} // namespace Lexer
