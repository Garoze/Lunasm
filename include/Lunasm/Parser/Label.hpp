#pragma once

#include <cstdint>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "Parser/Instruction.hpp"

namespace Parser {

class Label : public Instruction
{
public:
    Label(std::string_view);
    Label(std::string_view, std::uint16_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

    void update_address(std::uint16_t);

private:
    std::string_view m_label;
    std::uint16_t m_address;
};

} // namespace Parser
