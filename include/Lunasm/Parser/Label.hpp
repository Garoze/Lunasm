#pragma once

#include <cstdint>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "Parser/Opcodes.hpp"

namespace Lunasm {

class Label
{
public:
    Label(std::string_view);
    Label(std::string_view, std::uint16_t);

public:
    void print() const;

    void set_address(std::uint16_t);
    void set_label(std::string_view);

    std::uint16_t address() const;
    std::string_view label() const;

    void eval(std::vector<std::uint8_t>&,
              std::unordered_map<std::string_view, std::uint16_t>&) const;

private:
    std::string_view m_label;
    std::uint16_t m_address;
};

} // namespace Lunasm
