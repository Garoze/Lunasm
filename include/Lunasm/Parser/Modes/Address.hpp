#pragma once

#include "Parser/Operand.hpp"

#include "Parser/Instruction.hpp"

namespace Parser {

class Address : public Instruction
{
public:
    [[nodiscard]] const Operand& dst() const;
    [[nodiscard]] const Operand& src() const;

    virtual std::string as_string() const = 0;

protected:
    Address(Instruction::kind_t, Operand::value_t, Operand::value_t);

    Operand m_dst;
    Operand m_src;
};

} // namespace Parser
