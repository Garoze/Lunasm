#include "Lexer/Kind.hpp"
#include "Lexer/Mnemonics.hpp"

namespace Lunasm {

Kind::Kind(TokenKind kind)
    : m_kind(kind)
{}

std::string Kind::as_string() const
{
    return MNEMONICS.at(m_kind);
}

TokenKind Kind::raw() const {
    return m_kind;
}

}  // namespace Lunasm
