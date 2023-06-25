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
    Instruction(Opcode op, std::size_t size);
    Instruction(Opcode op, std::size_t size, Operand dst);
    Instruction(Opcode op, std::size_t size, Operand dst, Operand src);

    void print() const;
    std::size_t size() const;
    std::vector<std::uint8_t> eval() const;

private:
    Opcode m_opcode;
    std::size_t m_size;
    Operand m_dst;
    Operand m_src;
};

}  // namespace Lunasm
