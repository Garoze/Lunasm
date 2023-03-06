#pragma once

#include <string_view>
#include <unordered_map>

#include "Kind.hpp"

namespace Lunasm {

const std::unordered_map<std::string_view, L16TokenKind> INSTRUCTIONS = {
    {"nop", L16TokenKind::NOP},

    {"lda", L16TokenKind::LoadInstruction},
    {"sta", L16TokenKind::StoreInstruction},

    {"shl", L16TokenKind::ShiftLeft},
    {"shr", L16TokenKind::ShiftRight},

    {"and", L16TokenKind::BitAND},
    {"bor", L16TokenKind::BitOR},
    {"xor", L16TokenKind::BitXOR},
    {"not", L16TokenKind::BitNOT},

    {"psh", L16TokenKind::Push},
    {"pop", L16TokenKind::Pop},
};

static bool is_instruction(std::string_view inst)
{
    return INSTRUCTIONS.find(inst) != INSTRUCTIONS.end();
}

}  // namespace Lunasm
