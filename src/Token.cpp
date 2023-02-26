#include "Token.hpp"

#include "Mnemonics.hpp"

namespace Lunasm {

Token::Token(Kind kind, std::size_t line, std::size_t offset, std::string_view text)
    : m_kind(kind)
    , m_line(line)
    , m_offset(offset)
    , m_text(text)
{}

std::string Token::as_string() const
{
    return MNEMONICS.at(m_kind);
}

}  // namespace Lunasm
