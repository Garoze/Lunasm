#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

class Subroutine : public Instruction
{
public:
    Subroutine(Operand::value_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

private:
    Operand m_dst;
};

class Return : public Instruction
{
public:
    Return();

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;
};
} // namespace Parser
