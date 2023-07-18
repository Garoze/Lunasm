#pragma once

#include <cstdint>
#include <string_view>
#include <variant>
#include <vector>

#include "Parser/Opcodes.hpp"

namespace Lunasm {

using Operand =
    std::variant<std::monostate, std::uint8_t, std::uint16_t, std::string_view>;

class Instruction
{
public:
    Instruction(Opcode op, std::size_t size);
    Instruction(Opcode op, std::size_t size, Operand dst);
    Instruction(Opcode op, std::size_t size, Operand dst, Operand src);

    void print() const;
    std::size_t size() const;

    void set_dst(Operand);
    void set_src(Operand);

    void eval(std::vector<std::uint8_t>& out) const;

private:
    Opcode m_opcode;
    std::size_t m_size;
    Operand m_dst;
    Operand m_src;
};

} // namespace Lunasm
