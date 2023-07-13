#pragma once

#include <cstdint>
#include <string_view>

#include "Parser/Opcodes.hpp"

namespace Lunasm {

class Label
{
public:
    Label(std::string_view label);
    Label(std::string_view label, std::uint16_t address);

    void set_address(std::uint16_t address);
    void set_label(std::string_view label);

    std::uint16_t address() const;
    std::string_view label() const;

private:
    std::string_view m_label;
    std::uint16_t m_address;
};

} // namespace Lunasm
