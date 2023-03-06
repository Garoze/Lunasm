#pragma once

#include <unordered_map>

#include "Kind.hpp"

namespace Lunasm {

const std::unordered_map<L16TokenKind, std::string> MNEMONICS = {

    // CPU Instructions
    {L16TokenKind::NOP, "NOP"},

    {L16TokenKind::LoadInstruction, "LoadInstruction"},
    {L16TokenKind::StoreInstruction, "StoreInstruction"},

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
