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
    fmt::print("Token( T: {:8} Kind: {:18} Line: {:2}, Offset: {:2d} )\n", m_text, m_kind.as_string(), m_line, m_offset);
}

}  // namespace Lunasm
