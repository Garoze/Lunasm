#include "Parser/Modes/Absolute.hpp"

namespace Parser {

Absolute::Absolute(Instruction::kind_t kind, Operand::value_t src)
    : Instruction{ kind }
    , m_src(src)
{}

const Operand& Absolute::src() const
{
    return m_src;
}

} // namespace Parser
