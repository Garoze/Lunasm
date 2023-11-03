#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

#include "Modes/Absolute.hpp"

namespace Parser {

class Jump : public Absolute
{
public:
    Jump(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class JumpIfEquals : public Absolute
{
public:
    JumpIfEquals(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class JumpIfNotEquals : public Absolute
{
public:
    JumpIfNotEquals(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

} // namespace Parser
