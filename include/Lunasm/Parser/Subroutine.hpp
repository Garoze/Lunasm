#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

#include "Modes/Absolute.hpp"
#include "Modes/Implicit.hpp"

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
