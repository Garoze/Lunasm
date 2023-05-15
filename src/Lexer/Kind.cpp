#include "Lexer/Kind.hpp"
#include "Lexer/Mnemonics.hpp"

namespace Lunasm {

Kind::Kind(TokenKind kind)
    : m_value(kind)
{}

TokenKind Kind::raw() const
{
    return m_value;
}

std::string Kind::as_string() const
{
    return MNEMONICS.at(m_value);
}

}  // namespace Lunasm
