#include <cstdint>
#include <unordered_map>
#include <variant>
#include <vector>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include "Parser/Instruction.hpp"

namespace Lunasm {

const std::unordered_map<Opcode, std::string> OP_MNEMONICS = {
    {Opcode::NOP, "NOP"},
    {Opcode::LoadImmediate, "LoadImmediate"},
    {Opcode::LoadAddress, "LoadAddress"},
    {Opcode::LoadRegister, "LoadRegister"},

    {Opcode::StoreImmediate, "StoreImmediate"},
    {Opcode::StoreAddress, "StoreAddress"},
    {Opcode::StoreRegister, "StoreRegister"},

    {Opcode::ShiftLeft, "ShiftLeft"},
    {Opcode::ShiftRight, "ShiftRight"},

    {Opcode::BitwiseAND, "BitwiseAND"},
    {Opcode::BitwiseOR, "BitwiseOR"},
    {Opcode::BitwiseNOT, "BitwiseNOT"},
    {Opcode::BitwiseXOR, "BitwiseXOR"},

    {Opcode::PushImmediate, "PushImmediate"},
    {Opcode::PushAddress, "PushAddress"},
    {Opcode::PushRegister, "PushRegister"},
    {Opcode::Pop, "Pop"},

    {Opcode::Increment, "Increment"},
    {Opcode::Decrement, "Decrement"},

    {Opcode::AddImmediate, "AddImmediate"},
    {Opcode::AddAddress, "AddAddress"},
    {Opcode::AddRegister, "AddRegister"},

    {Opcode::SubImmediate, "SubImmediate"},
    {Opcode::SubAddress, "SubAddress"},
    {Opcode::SubRegister, "SubRegister"},

    {Opcode::MulImmediate, "MulImmediate"},
    {Opcode::MulAddress, "MulAddress"},
    {Opcode::MulRegister, "MulRegister"},

    {Opcode::DivImmediate, "DivImmediate"},
    {Opcode::DivAddress, "DivAddress"},
    {Opcode::DivRegister, "DivRegister"},

    {Opcode::ModImmediate, "ModImmediate"},
    {Opcode::ModAddress, "ModAddress"},
    {Opcode::ModRegister, "ModRegister"},

    {Opcode::CompareImmediate, "CompareImmediate"},
    {Opcode::CompareAddress, "CompareAddress"},
    {Opcode::CompareRegister, "CompareRegister"},

    {Opcode::Jump, "Jump"},
    {Opcode::JumpEquals, "JumpIfEquals"},
    {Opcode::JumpNotEquals, "JumpIfNotEquals"},

    {Opcode::Subroutine, "Subroutine"},
    {Opcode::Return, "Return"},
    {Opcode::Halt, "Halt"},
};

Instruction::Instruction(Opcode op, std::size_t size)
    : m_opcode(op)
    , m_size(size)
{}

Instruction::Instruction(Opcode op, std::size_t size, Operand dst = {},
                         Operand src = {})
    : m_opcode(op)
    , m_size(size)
    , m_dst(dst)
    , m_src(src)
{}

Instruction::Instruction(Opcode op, std::size_t size, Operand dst = {})
    : m_opcode(op)
    , m_size(size)
    , m_dst(dst)
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

    auto visitor = [&](auto arg) {
        using T = decltype(arg);

        if constexpr (std::is_same_v<T, std::uint8_t>)
        {
            output.push_back(arg);
        }
        else if constexpr (std::is_same_v<T, std::uint16_t>)
        {
            std::uint8_t LSB = (arg & 0x00FF);
            std::uint8_t MSB = (arg & 0xFF00) >> 8;

            output.push_back(LSB);
            output.push_back(MSB);
        }
    };

    std::visit(visitor, m_dst);
    std::visit(visitor, m_src);

    return output;
}

} // namespace Lunasm
