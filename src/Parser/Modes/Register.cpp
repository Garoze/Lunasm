#include "Parser/Modes/Register.hpp"

namespace Parser {

Register::Register(Instruction::kind_t kind, Operand::value_t dst,
                   Operand::value_t src)
    : Instruction{ kind }
    , m_dst(dst)
    , m_src(src)
{}

const Operand& Register::dst() const
{
    return m_dst;
}

const Operand& Register::src() const
{
    return m_src;
}

} // namespace Parser
