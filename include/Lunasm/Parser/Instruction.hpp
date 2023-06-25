#pragma once

#include <vector>
#include <variant>
#include <cstdint>

#include "Parser/Opcodes.hpp"

namespace Lunasm {

using Operand = std::variant<std::monostate, std::uint8_t, std::uint16_t>;

class Instruction
{
public:
    Instruction(Opcode op, Operand dst, Operand src, std::size_t size);

    void print() const;
    std::size_t size() const;
    std::vector<std::uint8_t> eval() const;

private:
    Opcode m_opcode;
    Operand m_dst;
    Operand m_src;
    std::size_t m_size;
};

}  // namespace Lunasm
