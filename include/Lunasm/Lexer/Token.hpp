#pragma once

#include <string>
#include <variant>
#include <unordered_map>

#include "Kind.hpp"

namespace Lunasm {

using Value = std::variant<std::string_view, std::uint8_t, std::uint16_t>;

class Token
{
public:
    Token(Kind, std::size_t, std::size_t, std::string_view);

    void print() const;

    TokenKind kind() const;

    std::string as_string() const;

    std::string_view text() const;

    constexpr explicit operator bool() noexcept { return true; }

private:
    Kind m_kind;
    std::size_t m_line;
    std::size_t m_offset;
    std::string_view m_text;
};

}  // namespace Lunasm
