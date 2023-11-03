#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

class Direct : public Instruction
{
public:
    [[nodiscard]] const Operand& dst() const;

    virtual std::string as_string() const = 0;

protected:
    Direct(Instruction::kind_t, Operand::value_t);

    Operand m_dst;
};

} // namespace Parser
