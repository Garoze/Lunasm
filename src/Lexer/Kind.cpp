#include "Lexer/Kind.hpp"
#include "Lexer/Mnemonics.hpp"

namespace Lexer {

Kind::Kind(kind_t kind)
    : m_kind(kind)
{}

Kind::kind_t Kind::raw() const
{
    return m_kind;
}

std::string Kind::as_string() const
{
    return KIND_TO_STR.at(m_kind);
}

} // namespace Lexer
