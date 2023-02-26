#include "Kind.hpp"
#include "Mnemonics.hpp"

namespace Lunasm {

Kind::Kind(L16TokenKind kind)
    : m_kind(kind)
{}

std::string Kind::as_string() const
{
    return MNEMONICS.at(m_kind);
}

}  // namespace Lunasm
