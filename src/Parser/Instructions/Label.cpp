#include <vector>

#include "fmt/core.h"

#include "Parser/Instructions/Label.hpp"

namespace Parser {

Label::Label(std::string_view label)
    : Instruction{ kind_t::Label }
    , m_label(label)
    , m_address(0)
{}

Label::Label(std::string_view label, std::uint16_t address = 0)
    : Instruction{ kind_t::Label }
    , m_label(label)
    , m_address(address)
{}

std::string Label::as_string() const
{
    return fmt::format("( Label: \"{}\" Address: \"{}\" )", m_label, m_address);
}

void Label::update_address(std::uint16_t new_address)
{
    m_address = new_address;
}

} // namespace Parser
