#pragma once

#include "Parser/Instruction.hpp"
namespace Parser {

class Nop : public Instruction
{
public:
    Nop();

    [[nodiscard]] virtual std::string as_string() const override;
};

} // namespace Parser
