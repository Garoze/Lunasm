#pragma once

#include <string>
#include <string_view>
#include <variant>

#include "Kind.hpp"

using TokenValue = std::variant<std::monostate, std::uint8_t, std::uint16_t, std::string_view>;

namespace Lunasm {

class Token
{
public:
    Token(Kind, TokenValue, std::size_t, std::size_t);

    void print() const;

    TokenKind kind() const;
    TokenValue raw_value() const;

public:
    std::string as_text() const;
    std::string as_string() const;

public:
    constexpr explicit operator bool() noexcept
    {
        return true;
    }

private:
    Kind m_kind;
    TokenValue m_value;
    std::size_t m_line;
    std::size_t m_offset;
};

} // namespace Lunasm
