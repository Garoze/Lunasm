#pragma once

#include "Parser/Absolute.hpp"
#include "Parser/Implicit.hpp"
#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

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
