#include "Parser/Direct.hpp"

namespace Parser {

Direct::Direct(Instruction::kind_t kind, Operand::value_t dst)
    : Instruction{ kind }
    , m_dst(dst)
{}

const Operand& Direct::dst() const
{
    return m_dst;
}

} // namespace Parser
