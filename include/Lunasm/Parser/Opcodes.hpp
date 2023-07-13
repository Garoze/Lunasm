#pragma once

#include <sys/wait.h>
#include <cstdint>

namespace Lunasm {

enum class Opcode : std::uint8_t {
    NOP,

    LoadImmediate,
    LoadAddress,
    LoadRegister,

    StoreImmediate,
    StoreAddress,
    StoreRegister,

    ShiftLeft,
    ShiftRight,

    BitwiseAND,
    BitwiseOR,
    BitwiseNOT,
    BitwiseXOR,

    PushImmediate,
    PushAddress,
    PushRegister,
    Pop,

    Increment,
    Decrement,

    AddImmediate,
    AddAddress,
    AddRegister,

    SubImmediate,
    SubAddress,
    SubRegister,

    MulImmediate,
    MulAddress,
    MulRegister,

    DivImmediate,
    DivAddress,
    DivRegister,

    ModImmediate,
    ModAddress,
    ModRegister,

    CompareImmediate,
    CompareAddress,
    CompareRegister,

    Jump,
    JumpEquals,
    JumpNotEquals,

    Subroutine,
    Return,
    Halt,
};

}  // namespace Lunasm
