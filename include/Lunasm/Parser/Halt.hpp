#pragma once

#include "Parser/Instruction.hpp"

namespace Parser {

class Halt : public Instruction
{
public:
    Halt();

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;
};

} // namespace Parser
