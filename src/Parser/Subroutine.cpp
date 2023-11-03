#include "Parser/Subroutine.hpp"
#include "fmt/core.h"

namespace Parser {

Subroutine::Subroutine(Operand::value_t dst)
    : Absolute{ kind_t::Subroutine, dst }
{}

std::string Subroutine::as_string() const
{
    return fmt::format("( Subroutine dst: \"{}\" )", m_src.as_string());
}

Return::Return()
    : Implicit{ kind_t::Return }
{}

std::string Return::as_string() const
{
    return fmt::format("( Return )");
}

} // namespace Parser
