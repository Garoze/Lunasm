#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

#include "Modes/Address.hpp"
#include "Modes/Immediate.hpp"
#include "Modes/Register.hpp"

namespace Parser {

class CompareImmediate : public Immediate
{
public:
    CompareImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class CompareAddress : public Address
{
public:
    CompareAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class CompareRegister : public Register
{
public:
    CompareRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

} // namespace Parser
