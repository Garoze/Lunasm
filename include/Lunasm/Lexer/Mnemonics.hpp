#pragma once

#include <unordered_map>

#include "Kind.hpp"

namespace Lunasm {

const std::unordered_map<TokenKind, std::string> MNEMONICS = {

    // CPU Instructions
    {TokenKind::NOP, "NOP"},

    {TokenKind::MovInstruction, "MovInstruction"},

    {TokenKind::ShiftLeft, "ShiftLeft"},
    {TokenKind::ShiftRight, "ShiftRight"},

    {TokenKind::BitAND, "BitwiseAND"},
    {TokenKind::BitOR, "BitwiseOR"},
    {TokenKind::BitXOR, "BitwiseXOR"},
    {TokenKind::BitNOT, "BitwiseNOT"},

    {TokenKind::Push, "Push"},
    {TokenKind::Pop, "Pop"},

    {TokenKind::Increment, "Increment"},
    {TokenKind::Decrement, "Decrement"},

    {TokenKind::Add, "Add"},
    {TokenKind::Sub, "Sub"},
    {TokenKind::Mul, "Mul"},
    {TokenKind::Mod, "Mod"},

    {TokenKind::Compare, "Compare"},

    {TokenKind::Jump, "Jump"},
    {TokenKind::JumpEquals, "JumpEquals"},
    {TokenKind::JumpNotEquals, "JumpNotEquals"},

    {TokenKind::Subroutine, "Subroutine"},

    {TokenKind::Return, "Return"},

    {TokenKind::Halt, "Halt"},

    // Lexer things
    {TokenKind::Label, "Label"},
    {TokenKind::Register, "Register"},
    {TokenKind::Immediate, "Immediate"},

    // Literals
    {TokenKind::OpenBracket, "OpenBracket"},
    {TokenKind::CloseBracket, "CloseBracket"},

    {TokenKind::AddOperation, "AddOperation"},
    {TokenKind::SubOperation, "SubOperation"},

    {TokenKind::Colon, "Colon"},
    {TokenKind::Comma, "Comma"},

    {TokenKind::END, "EOF"},
};

}  // namespace Lunasm
