#include "Parser/Label.hpp"

namespace Lunasm {

Label::Label(std::string_view label)
    : m_label(label)
{}

Label::Label(std::string_view label, std::uint16_t address)
    : m_label(label)
    , m_address(address)
{}

void Label::set_address(std::uint16_t address)
{
    m_address = address;
}

void Label::set_label(std::string_view label)
{
    m_label = label;
}

std::uint16_t Label::address() const
{
    return m_address;
}

std::string_view Label::label() const
{
    return m_label;
}

}  // namespace Lunasm
