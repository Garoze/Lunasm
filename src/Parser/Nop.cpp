#include "Parser/Nop.hpp"
#include "fmt/core.h"

namespace Parser {

Nop::Nop()
    : Instruction(kind_t::Nop)
{}

std::string Nop::as_string() const
{
    return fmt::format("( Nop )");
}

} // namespace Parser
