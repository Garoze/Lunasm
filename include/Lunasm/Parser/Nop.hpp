#pragma once

#include "Modes/Implicit.hpp"

namespace Parser {

class Nop : public Implicit
{
public:
    Nop();

    [[nodiscard]] virtual std::string as_string() const override;
};

} // namespace Parser
