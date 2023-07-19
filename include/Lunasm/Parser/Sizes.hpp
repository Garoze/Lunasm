#pragma once

#include <unordered_map>

#include "Parser/Opcodes.hpp"

namespace Lunasm {

const std::unordered_map<Opcode, std::size_t> INST_SIZE = {
    {Opcode::NOP, 1},

    {Opcode::LoadImmediate, 4},
    {Opcode::LoadAddress, 4},
    {Opcode::LoadRegister, 3},

    {Opcode::StoreImmediate, 5},
    {Opcode::StoreAddress, 5},
    {Opcode::StoreRegister, 4},

    {Opcode::ShiftLeft, 4},
    {Opcode::ShiftRight, 4},

    {Opcode::BitwiseAND, 4},
    {Opcode::BitwiseOR, 4},
    {Opcode::BitwiseNOT, 2},
    {Opcode::BitwiseXOR, 4},

    {Opcode::PushImmediate, 3},
    {Opcode::PushAddress, 3},
    {Opcode::PushRegister, 2},
    {Opcode::Pop, 2},

    {Opcode::Increment, 2},
    {Opcode::Decrement, 2},

    {Opcode::AddImmediate, 4},
    {Opcode::AddAddress, 5},
    {Opcode::AddRegister, 3},

    {Opcode::SubImmediate, 4},
    {Opcode::SubAddress, 5},
    {Opcode::SubRegister, 3},

    {Opcode::MulImmediate, 4},
    {Opcode::MulAddress, 5},
    {Opcode::MulRegister, 3},

    {Opcode::DivImmediate, 4},
    {Opcode::DivAddress, 5},
    {Opcode::DivRegister, 3},

    {Opcode::ModImmediate, 4},
    {Opcode::ModAddress, 5},
    {Opcode::ModRegister, 3},

    {Opcode::CompareImmediate, 4},
    {Opcode::CompareAddress, 5},
    {Opcode::CompareRegister, 3},

    {Opcode::Jump, 3},
    {Opcode::JumpEquals, 3},
    {Opcode::JumpNotEquals, 3},

    {Opcode::Subroutine, 2},
    {Opcode::Return, 1},
    {Opcode::Halt, 1},
};

} // namespace Lunasm
