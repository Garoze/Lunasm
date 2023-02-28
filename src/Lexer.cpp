#include "Lexer.hpp"

namespace Lunasm {

Lexer::Lexer(const std::string& source_code)
    : m_line(1)
    , m_index(0)
    , m_source_code(source_code)
{}

char Lexer::eat()
{
    return m_source_code.at(m_index++);
}

}  // namespace Lunasm
