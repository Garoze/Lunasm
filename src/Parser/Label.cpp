#include "Parser/Label.hpp"

namespace Lunasm {

Label::Label(Opcode op, std::string label)
    : m_opcode(op)
    , m_label(label)
{}

Label::Label(Opcode op, std::string label, std::uint16_t address)
    : m_opcode(op)
    , m_label(label)
    , m_address(address)
{}

void Label::set_label(std::string label)
{
    m_label = label;
}

void Label::set_address(std::uint16_t address)
{
    m_address = address;
}

std::string Label::label() const
{
    return m_label;
}

std::uint16_t Label::address() const
{
    return m_address;
}

}  // namespace Lunasm
