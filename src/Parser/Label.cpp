#include <vector>

#include "fmt/core.h"

#include "Parser/Label.hpp"

namespace Lunasm {

Label::Label(std::string_view label)
    : m_label(label)
    , m_address(0)
{}

Label::Label(std::string_view label, std::uint16_t address)
    : m_label(label)
    , m_address(address)
{}

void Label::print() const
{
    fmt::print("( {} :: {:04x} )\n", m_label, m_address);
}

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

void Label::eval(std::vector<std::uint8_t>& output) const
{
    std::uint8_t LSB = (m_address & 0x00FF);
    std::uint8_t MSB = (m_address & 0xFF00) >> 8;

    output.push_back(LSB);
    output.push_back(MSB);
}

} // namespace Lunasm
