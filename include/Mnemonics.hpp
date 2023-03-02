#pragma once

#include <unordered_map>

#include "Kind.hpp"

namespace Lunasm {

const std::unordered_map<L16TokenKind, std::string> MNEMONICS = {
    {L16TokenKind::NOP, "NOP"},

    {L16TokenKind::LoadImmediate, "LoadImmediate"},
    {L16TokenKind::LoadAddress, "LoadAddress"},

    {L16TokenKind::Register, "Register"},

    {L16TokenKind::Immediate, "Immediate"},

    {L16TokenKind::Label, "Label"},

    {L16TokenKind::END, "EOF"},
};

}  // namespace Lunasm
