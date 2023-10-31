#include "fmt/core.h"

#include "Parser/Halt.hpp"

namespace Parser {

Halt::Halt()
    : Instruction{ kind_t::Halt }
{}

std::string Halt::as_string() const
{
    return fmt::format("( Halt )");
}

} // namespace Parser
