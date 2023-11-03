#pragma once

#include "Parser/Operand.hpp"

#include "Parser/Instructions/Instruction.hpp"

#include "Parser/Modes/Absolute.hpp"
#include "Parser/Modes/Direct.hpp"
#include "Parser/Modes/Reference.hpp"

namespace Parser {

class PushImmediate : public Reference
{
public:
    PushImmediate(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class PushAddress : public Absolute
{
public:
    PushAddress(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class PushRegister : public Direct
{
public:
    PushRegister(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class Pop : public Direct
{
public:
    Pop(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

} // namespace Parser
