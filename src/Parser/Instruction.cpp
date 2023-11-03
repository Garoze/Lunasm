#include <cstdint>
#include <stdexcept>
#include <unordered_map>
#include <variant>
#include <vector>

#include "fmt/core.h"
#include "fmt/ranges.h"

#include "Parser/Instruction.hpp"

namespace Parser {

const std::unordered_map<Instruction::kind_t, std::string> INST_AS_STR = {
    { Instruction::kind_t::Nop, "Nop" },
    { Instruction::kind_t::LoadImmediate, "LoadImmediate" },
    { Instruction::kind_t::LoadAddress, "LoadAddress" },
    { Instruction::kind_t::LoadRegister, "LoadRegister" },

    { Instruction::kind_t::StoreImmediate, "StoreImmediate" },
    { Instruction::kind_t::StoreAddress, "StoreAddress" },
    { Instruction::kind_t::StoreRegister, "StoreRegister" },

    { Instruction::kind_t::ShiftLeft, "ShiftLeft" },
    { Instruction::kind_t::ShiftRight, "ShiftRight" },

    { Instruction::kind_t::And, "BitwiseAND" },
    { Instruction::kind_t::Or, "BitwiseOR" },
    { Instruction::kind_t::Not, "BitwiseNOT" },
    { Instruction::kind_t::Xor, "BitwiseXOR" },

    { Instruction::kind_t::PushImmediate, "PushImmediate" },
    { Instruction::kind_t::PushAddress, "PushAddress" },
    { Instruction::kind_t::PushRegister, "PushRegister" },
    { Instruction::kind_t::Pop, "Pop" },

    { Instruction::kind_t::Increment, "Increment" },
    { Instruction::kind_t::Decrement, "Decrement" },

    { Instruction::kind_t::AddImmediate, "AddImmediate" },
    { Instruction::kind_t::AddAddress, "AddAddress" },
    { Instruction::kind_t::AddRegister, "AddRegister" },

    { Instruction::kind_t::SubImmediate, "SubImmediate" },
    { Instruction::kind_t::SubAddress, "SubAddress" },
    { Instruction::kind_t::SubRegister, "SubRegister" },

    { Instruction::kind_t::MulImmediate, "MulImmediate" },
    { Instruction::kind_t::MulAddress, "MulAddress" },
    { Instruction::kind_t::MulRegister, "MulRegister" },

    { Instruction::kind_t::DivImmediate, "DivImmediate" },
    { Instruction::kind_t::DivAddress, "DivAddress" },
    { Instruction::kind_t::DivRegister, "DivRegister" },

    { Instruction::kind_t::ModImmediate, "ModImmediate" },
    { Instruction::kind_t::ModAddress, "ModAddress" },
    { Instruction::kind_t::ModRegister, "ModRegister" },

    { Instruction::kind_t::CompareImmediate, "CompareImmediate" },
    { Instruction::kind_t::CompareAddress, "CompareAddress" },
    { Instruction::kind_t::CompareRegister, "CompareRegister" },

    { Instruction::kind_t::Jump, "Jump" },
    { Instruction::kind_t::JumpIfEquals, "JumpIfEquals" },
    { Instruction::kind_t::JumpIfNotEquals, "JumpIfNotEquals" },

    { Instruction::kind_t::Subroutine, "Subroutine" },
    { Instruction::kind_t::Return, "Return" },
    { Instruction::kind_t::Halt, "Halt" },
};

Instruction::Instruction(kind_t kind)
    : m_kind(kind)
{}

Instruction::kind_t Instruction::raw() const
{
    return m_kind;
}

std::string Instruction::as_string() const
{
    return INST_AS_STR.at(m_kind);
}

} // namespace Parser
