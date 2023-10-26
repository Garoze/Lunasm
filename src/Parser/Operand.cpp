#include "Parser/Operand.hpp"
#include <string>

namespace Parser {

Operand::Operand()
{}

Operand::Operand(value_t value)
    : m_value(value)
{}

Operand::value_t Operand::raw() const
{
    return m_value;
}

std::string Operand::as_string() const
{
    auto visitor = [&](auto& arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::monostate>)
        {
            return "";
        }
        else if constexpr (std::is_same_v<T, std::uint16_t>)
        {
            return std::to_string(arg);
        }
        else if constexpr (std::is_same_v<T, std::string_view>)
        {
            return std::string{ arg };
        }
    };

    return std::visit(visitor, m_value);
}

} // namespace Parser
