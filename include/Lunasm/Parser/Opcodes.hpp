#pragma once

#include <cstdint>

namespace Lunasm {

enum class Opcode : std::uint8_t {
    NOP,
    LoadImmediate,
    LoadRegister,
    LoadAddress,
};

}  // namespace Lunasm
