#include "fmt/core.h"

#include "Token.hpp"

namespace Lunasm {

Token::Token(Kind kind, std::size_t line, std::size_t offset, std::string_view text)
    : m_kind(Kind(kind))
    , m_line(line)
    , m_offset(offset)
    , m_text(text)
{}

void Token::print() const
{
    auto text = fmt::format("\"{}\"", m_text);
    auto kind = fmt::format("<{}>", m_kind.as_string());

    fmt::print("Token( Kind: {:10} Text: {:8} Line: {:2d} Offset: {:2d})\n", kind, text, m_line, m_offset);
}

}  // namespace Lunasm
