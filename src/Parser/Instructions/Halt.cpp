#include "fmt/core.h"

#include "Parser/Instructions/Halt.hpp"

namespace Parser {

Halt::Halt()
    : Implicit{ kind_t::Halt }
{}

std::string Halt::as_string() const
{
    return fmt::format("( Halt )");
}

} // namespace Parser
