#pragma once

#include <unordered_map>

#include "Parser/Instruction.hpp"

namespace Parser {

const std::unordered_map<Instruction::kind_t, std::size_t> INST_SIZE = {
    { Instruction::kind_t::Nop, 1 },

    { Instruction::kind_t::LoadImmediate, 4 },
    { Instruction::kind_t::LoadAddress, 4 },
    { Instruction::kind_t::LoadRegister, 3 },

    { Instruction::kind_t::StoreImmediate, 5 },
    { Instruction::kind_t::StoreAddress, 5 },
    { Instruction::kind_t::StoreRegister, 4 },

    { Instruction::kind_t::ShiftLeft, 4 },
    { Instruction::kind_t::ShiftRight, 4 },

    { Instruction::kind_t::And, 4 },
    { Instruction::kind_t::Or, 4 },
    { Instruction::kind_t::Xor, 2 },
    { Instruction::kind_t::Not, 4 },

    { Instruction::kind_t::PushImmediate, 3 },
    { Instruction::kind_t::PushAddress, 3 },
    { Instruction::kind_t::PushRegister, 2 },
    { Instruction::kind_t::Pop, 2 },

    { Instruction::kind_t::Increment, 2 },
    { Instruction::kind_t::Decrement, 2 },

    { Instruction::kind_t::AddImmediate, 4 },
    { Instruction::kind_t::AddAddress, 5 },
    { Instruction::kind_t::AddRegister, 3 },

    { Instruction::kind_t::SubImmediate, 4 },
    { Instruction::kind_t::SubAddress, 5 },
    { Instruction::kind_t::SubRegister, 3 },

    { Instruction::kind_t::MulImmediate, 4 },
    { Instruction::kind_t::MulAddress, 5 },
    { Instruction::kind_t::MulRegister, 3 },

    { Instruction::kind_t::DivImmediate, 4 },
    { Instruction::kind_t::DivAddress, 5 },
    { Instruction::kind_t::DivRegister, 3 },

    { Instruction::kind_t::ModImmediate, 4 },
    { Instruction::kind_t::ModAddress, 5 },
    { Instruction::kind_t::ModRegister, 3 },

    { Instruction::kind_t::CompareImmediate, 4 },
    { Instruction::kind_t::CompareAddress, 5 },
    { Instruction::kind_t::CompareRegister, 3 },

    { Instruction::kind_t::Jump, 3 },
    { Instruction::kind_t::JumpIfEquals, 3 },
    { Instruction::kind_t::JumpIfNotEquals, 3 },

    { Instruction::kind_t::Subroutine, 2 },
    { Instruction::kind_t::Return, 1 },
    { Instruction::kind_t::Halt, 1 },
};

} // namespace Parser
