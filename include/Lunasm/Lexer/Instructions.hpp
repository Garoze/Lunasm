#pragma once

#include <string_view>
#include <unordered_map>

#include "Kind.hpp"

namespace Lunasm {

const std::unordered_map<std::string_view, TokenKind> INSTRUCTIONS = {
    {"nop", TokenKind::NOP},

    {"mov", TokenKind::MovInstruction},

    {"shl", TokenKind::ShiftLeft},
    {"shr", TokenKind::ShiftRight},

    {"and", TokenKind::BitAND},
    {"bor", TokenKind::BitOR},
    {"xor", TokenKind::BitXOR},
    {"not", TokenKind::BitNOT},

    {"psh", TokenKind::Push},
    {"pop", TokenKind::Pop},

    {"inc", TokenKind::Increment},
    {"dec", TokenKind::Decrement},

    {"add", TokenKind::Add},
    {"sub", TokenKind::Sub},
    {"mul", TokenKind::Mul},
    {"mod", TokenKind::Mod},

    {"cmp", TokenKind::Compare},

    {"jmp", TokenKind::Jump},
    {"jeq", TokenKind::JumpEquals},
    {"jne", TokenKind::JumpNotEquals},

    {"jsr", TokenKind::Subroutine},

    {"ret", TokenKind::Return},

    {"hlt", TokenKind::Halt},
};

static bool is_instruction(std::string_view inst)
{
    return INSTRUCTIONS.find(inst) != INSTRUCTIONS.end();
}

}  // namespace Lunasm
