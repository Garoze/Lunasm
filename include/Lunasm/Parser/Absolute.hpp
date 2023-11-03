#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

class Absolute : public Instruction
{
public:
    [[nodiscard]] const Operand& src() const;

    virtual std::string as_string() const = 0;

protected:
    Absolute(Instruction::kind_t, Operand::value_t);

    Operand m_src;
};

} // namespace Parser
