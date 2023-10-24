#include "fmt/core.h"

#include "Lexer/Location.hpp"

namespace Lexer {

Location::Location(std::string file, std::size_t line, std::size_t column)
    : m_file(file)
    , m_line(line)
    , m_column(column)
{}

std::string Location::file() const
{
    return m_file;
}

std::size_t Location::line() const
{
    return m_line;
}

std::size_t Location::column() const
{
    return m_column;
}

std::string Location::as_string() const
{
    return fmt::format("File: {} Line: {} Column: {}", m_file, m_line,
                       m_column);
}

} // namespace Lexer
