#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

#include "Modes/Address.hpp"
#include "Modes/Immediate.hpp"
#include "Modes/Register.hpp"

namespace Parser {

class StoreImmediate : public Immediate
{
public:
    StoreImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class StoreAddress : public Address
{
public:
    StoreAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class StoreRegister : public Register
{
public:
    StoreRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

} // namespace Parser
