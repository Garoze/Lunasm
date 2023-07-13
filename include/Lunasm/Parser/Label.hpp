#pragma once

#include <cstdint>
#include <string>

#include "Parser/Opcodes.hpp"

namespace Lunasm {

class Label
{
public:
    Label(Opcode op, std::string label);
    Label(Opcode op, std::string label, std::uint16_t address);

    void set_label(std::string label);
    void set_address(std::uint16_t address);

    std::string label() const;
    std::uint16_t address() const;

private:
    Opcode m_opcode;
    std::string m_label;
    std::uint16_t m_address;
};

}  // namespace Lunasm
