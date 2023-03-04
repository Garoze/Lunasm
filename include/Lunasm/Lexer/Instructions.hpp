#pragma once

#include <string_view>
#include <unordered_map>

#include "Kind.hpp"

namespace Lunasm {

const std::unordered_map<std::string_view, L16TokenKind> INSTRUCTIONS = {
    {"nop", L16TokenKind::NOP},

    {"ldi", L16TokenKind::LoadImmediate},
    {"lda", L16TokenKind::LoadAddress},
    {"ldr", L16TokenKind::LoadRegister},

    {"sti", L16TokenKind::StoreImmediate},
    {"sta", L16TokenKind::StoreAddress},
    {"str", L16TokenKind::StoreRegister},

    {"shl", L16TokenKind::ShiftLeft},
    {"shr", L16TokenKind::ShiftRight},
};

static bool is_instruction(std::string_view inst)
{
    return INSTRUCTIONS.find(inst) != INSTRUCTIONS.end();
}

}  // namespace Lunasm
