#pragma once

#include "Parser/Direct.hpp"
#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"
#include "Parser/Register.hpp"

namespace Parser {

class ShiftLeft : public Register
{
public:
    ShiftLeft(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class ShiftRight : public Register
{
public:
    ShiftRight(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class And : public Register
{
public:
    And(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class Or : public Register
{
public:
    Or(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class Xor : public Register
{
public:
    Xor(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class Not : public Direct
{
public:
    Not(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

} // namespace Parser
