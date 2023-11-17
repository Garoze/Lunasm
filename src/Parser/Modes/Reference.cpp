#include "Parser/Modes/Reference.hpp"

namespace Parser {

Reference::Reference(Instruction::kind_t kind, Operand::value_t src)
    : Instruction{ kind }
    , m_src(src)
{}

const Operand& Reference::src() const
{
    return m_src;
}

} // namespace Parser
