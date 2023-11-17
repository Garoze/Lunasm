#pragma once

#include "Parser/Instruction.hpp"

namespace Parser {

class Implicit : public Instruction
{
public:
    virtual std::string as_string() const = 0;

protected:
    Implicit(Instruction::kind_t);
};

} // namespace Parser
