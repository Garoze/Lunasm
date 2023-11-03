#pragma once

#include "Parser/Absolute.hpp"
#include "Parser/Direct.hpp"
#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"
#include "Parser/Reference.hpp"

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
