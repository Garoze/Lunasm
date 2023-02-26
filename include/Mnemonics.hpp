#pragma once

#include <unordered_map>

#include "Kind.hpp"

namespace Lunasm {

const std::unordered_map<L16TokenKind, std::string> MNEMONICS = {
    {L16TokenKind::NOP, "NOP"},
};

}  // namespace Lunasm
