#include "Parser/Modes/Address.hpp"

namespace Parser {

Address::Address(Instruction::kind_t kind, Operand::value_t dst,
                 Operand::value_t src)
    : Instruction{ kind }
    , m_dst(dst)
    , m_src(src)
{}

const Operand& Address::dst() const
{
    return m_dst;
}

const Operand& Address::src() const
{
    return m_src;
}

} // namespace Parser
