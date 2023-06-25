#pragma once

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
};

}  // namespace Lunasm
