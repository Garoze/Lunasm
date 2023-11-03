#include "Parser/Immediate.hpp"

namespace Parser {

Immediate::Immediate(Instruction::kind_t kind, Operand::value_t dst,
                     Operand::value_t src)
    : Instruction{ kind }
    , m_dst(dst)
    , m_src(src)
{}

const Operand& Immediate::dst() const
{
    return m_dst;
}

const Operand& Immediate::src() const
{
    return m_src;
}

} // namespace Parser
