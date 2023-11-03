#pragma once

#include "Parser/Modes/Implicit.hpp"

namespace Parser {

class Halt : public Implicit
{
public:
    Halt();

    [[nodiscard]] virtual std::string as_string() const override;
};

} // namespace Parser
