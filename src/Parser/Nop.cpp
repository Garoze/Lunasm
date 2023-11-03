#include "fmt/core.h"

#include "Parser/Nop.hpp"

namespace Parser {

Nop::Nop()
    : Implicit{ kind_t::Nop }
{}

std::string Nop::as_string() const
{
    return fmt::format("( Nop )");
}

} // namespace Parser
