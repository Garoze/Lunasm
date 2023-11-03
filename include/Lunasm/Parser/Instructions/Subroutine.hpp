#pragma once

#include "Parser/Operand.hpp"

#include "Parser/Instructions/Instruction.hpp"

#include "Parser/Modes/Absolute.hpp"
#include "Parser/Modes/Implicit.hpp"

namespace Parser {

class Subroutine : public Absolute
{
public:
    Subroutine(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class Return : public Implicit
{
public:
    Return();

    [[nodiscard]] virtual std::string as_string() const override;
};
} // namespace Parser
