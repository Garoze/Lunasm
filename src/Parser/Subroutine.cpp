#include "Parser/Subroutine.hpp"
#include "fmt/core.h"

namespace Parser {

Subroutine::Subroutine(Operand::value_t dst)
    : Instruction{ kind_t::Subroutine }
    , m_dst(dst)
{}

std::string Subroutine::as_string() const
{
    return fmt::format("( Subroutine dst: \"{}\" )", m_dst.as_string());
}

Return::Return()
    : Instruction{ kind_t::Return }
{}

std::string Return::as_string() const
{
    return fmt::format("( Return )");
}

} // namespace Parser
