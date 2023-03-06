#pragma once

#include <unordered_map>

#include "Kind.hpp"

namespace Lunasm {

const std::unordered_map<L16TokenKind, std::string> MNEMONICS = {

    // CPU Instructions
    {L16TokenKind::NOP, "NOP"},

    {L16TokenKind::LoadInstruction, "LoadInstruction"},
    {L16TokenKind::StoreInstruction, "StoreInstruction"},

    {L16TokenKind::ShiftLeft, "ShiftLeft"},
    {L16TokenKind::ShiftRight, "ShiftRight"},

    {L16TokenKind::BitAND, "BitwiseAND"},
    {L16TokenKind::BitOR, "BitwiseOR"},
    {L16TokenKind::BitXOR, "BitwiseXOR"},
    {L16TokenKind::BitNOT, "BitwiseNOT"},

    {L16TokenKind::Push, "Push"},
    {L16TokenKind::Pop, "Pop"},

    {L16TokenKind::Increment, "Increment"},
    {L16TokenKind::Decrement, "Decrement"},

    {L16TokenKind::Add, "Add"},
    {L16TokenKind::Sub, "Sub"},
    {L16TokenKind::Mul, "Mul"},
    {L16TokenKind::Mod, "Mod"},

    {L16TokenKind::Compare, "Compare"},

    {L16TokenKind::Jump, "Jump"},
    {L16TokenKind::JumpEquals, "JumpEquals"},
    {L16TokenKind::JumpNotEquals, "JumpNotEquals"},

    {L16TokenKind::Subroutine, "Subroutine"},

    {L16TokenKind::Return, "Return"},

    // Lexer things
    {L16TokenKind::Label, "Label"},
    {L16TokenKind::Register, "Register"},
    {L16TokenKind::Immediate, "Immediate"},

    // Literals
    {L16TokenKind::OpenBracket, "OpenBracket"},
    {L16TokenKind::CloseBracket, "CloseBracket"},

    {L16TokenKind::AddOperation, "AddOperation"},
    {L16TokenKind::SubOperation, "SubOperation"},

    {L16TokenKind::Colon, "Colon"},
    {L16TokenKind::Comma, "Comma"},

    {L16TokenKind::END, "EOF"},
};

}  // namespace Lunasm
