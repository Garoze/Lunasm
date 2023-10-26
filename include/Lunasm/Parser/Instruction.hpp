#pragma once

#include <cstdint>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

#include "Parser/Label.hpp"
#include "Parser/Opcodes.hpp"

namespace Parser {

using Operand =
    std::variant<std::monostate, std::uint8_t, std::uint16_t, std::string_view>;

class Instruction
{
public:
    Instruction(Opcode, std::size_t);
    Instruction(Opcode, std::size_t, Operand);
    Instruction(Opcode, std::size_t, Operand, Operand);

public:
    void print() const;
    void set_dst(Operand);
    void set_src(Operand);

    std::size_t size() const;

    void eval(std::vector<std::uint8_t>&,
              std::unordered_map<std::string_view, std::uint16_t>&) const;

private:
    void split_u16(std::vector<std::uint8_t>&, std::uint16_t) const;

private:
    Opcode m_opcode;
    std::size_t m_size;
    Operand m_dst;
    Operand m_src;
};

} // namespace Parser
