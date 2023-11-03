#pragma once

#include "Parser/Operand.hpp"

#include "Parser/Instructions/Instruction.hpp"

namespace Parser {

class Reference : public Instruction
{
public:
    [[nodiscard]] const Operand& src() const;

    virtual std::string as_string() const = 0;

protected:
    Reference(Instruction::kind_t, Operand::value_t);

    Operand m_src;
};

} // namespace Parser
