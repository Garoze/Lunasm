#pragma once

#include <unordered_map>

#include "Token.hpp"

namespace Lunasm {

const std::unordered_map<Kind, std::string> MNEMONICS = {
    {Kind::NOP, "NOP"},
};

}  // namespace Lunasm
