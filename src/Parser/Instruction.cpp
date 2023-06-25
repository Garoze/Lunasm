#include <variant>
#include <vector>
#include <cstdint>
#include <unordered_map>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include "Parser/Instruction.hpp"

namespace Lunasm {

const std::unordered_map<Opcode, std::string> OP_MNEMONICS = {
    { Opcode::NOP, "NOP" },
    { Opcode::LoadImmediate, "LoadImmediate" },
    { Opcode::LoadRegister, "LoadRegister" },
    { Opcode::LoadAddress, "LoadAddress" },
};

Instruction::Instruction(Opcode op, std::size_t size, Operand dst = {}, Operand src = {})
    : m_opcode(op)
    , m_size(size)
    , m_dst(dst)
    , m_src(src)
{}

void Instruction::print() const
{
    auto mem = fmt::format("{::02x}", eval());
    fmt::print("({} size: {}) -> {}\n", OP_MNEMONICS.at(m_opcode), m_size, mem);
}

std::size_t Instruction::size() const
{
    return m_size;
}

std::vector<std::uint8_t> Instruction::eval() const
{
    std::vector<std::uint8_t> output;
    output.push_back(static_cast<std::uint8_t>(m_opcode));

    if (auto dst = std::get_if<std::uint8_t>(&m_dst))
    {
        output.push_back(*dst);

        if (auto src = std::get_if<std::uint8_t>(&m_src))
        {
            output.push_back(*src);
        }
        else if (auto src = std::get_if<std::uint16_t>(&m_src))
        {
            std::uint8_t LSB = (*src & 0x00FF);
            std::uint8_t MSB = (*src & 0xFF00) >> 8;

            output.push_back(LSB);
            output.push_back(MSB);
        }
    }
    else if (auto dst = std::get_if<std::uint16_t>(&m_dst))
    {
        std::uint8_t LSB = (*dst & 0x00FF);
        std::uint8_t MSB = (*dst & 0xFF00) >> 8;

        output.push_back(LSB);
        output.push_back(MSB);

        if (auto src = std::get_if<std::uint8_t>(&m_src))
        {
            output.push_back(*src);
        }
        else if (auto src = std::get_if<std::uint16_t>(&m_src))
        {
            std::uint8_t LSB = (*src & 0x00FF);
            std::uint8_t MSB = (*src & 0xFF00) >> 8;

            output.push_back(LSB);
            output.push_back(MSB);
        }
    }

    return output;
}

}  // namespace Lunasm
