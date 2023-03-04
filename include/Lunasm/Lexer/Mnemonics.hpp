#pragma once

#include <unordered_map>

#include "Kind.hpp"

namespace Lunasm {

const std::unordered_map<L16TokenKind, std::string> MNEMONICS = {
    {L16TokenKind::NOP, "NOP"},

    {L16TokenKind::LoadImmediate, "LoadImmediate"},
    {L16TokenKind::LoadAddress, "LoadAddress"},
    {L16TokenKind::LoadRegister, "LoadRegister"},

    {L16TokenKind::StoreImmediate, "StoreImmediate"},
    {L16TokenKind::StoreAddress, "StoreAddress"},
    {L16TokenKind::StoreRegister, "StoreRegister"},

    {L16TokenKind::ShiftLeft, "ShiftLeft"},
    {L16TokenKind::ShiftRight, "ShiftRight"},

    {L16TokenKind::BitwiseAnd, "BitwiseAND"},
    {L16TokenKind::BitwiseOr, "BitwiseOR"},
    {L16TokenKind::BitwiseXor, "BitwiseXOR"},
    {L16TokenKind::BitwiseNot, "BitwiseNOT"},

    {L16TokenKind::CmpImmediate, "CompareImmediate"},
    {L16TokenKind::CmpAddress, "CompareAddress"},
    {L16TokenKind::CmpRegister, "CompareRegister"},

    {L16TokenKind::Jump, "Jump"},

    {L16TokenKind::Register, "Register"},

    {L16TokenKind::Immediate, "Immediate"},

    {L16TokenKind::Label, "Label"},

    {L16TokenKind::OpenBracket, "OpenBracket"},
    {L16TokenKind::CloseBracket, "CloseBracket"},

    {L16TokenKind::AddOperation, "AddOperation"},
    {L16TokenKind::SubOperation, "SubOperation"},

    {L16TokenKind::Colon, "Colon"},
    {L16TokenKind::Comma, "Comma"},

    {L16TokenKind::END, "EOF"},
};

}  // namespace Lunasm
