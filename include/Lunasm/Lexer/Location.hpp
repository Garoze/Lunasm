#pragma once

#include <string>
namespace Lexer {

class Location
{
public:
    Location(std::string, std::size_t, std::size_t);

    [[nodiscard]] std::string file() const;
    [[nodiscard]] std::size_t line() const;
    [[nodiscard]] std::size_t column() const;
    [[nodiscard]] std::string as_string() const;

private:
    std::string m_file;
    std::size_t m_line;
    std::size_t m_column;
};

} // namespace Lexer
