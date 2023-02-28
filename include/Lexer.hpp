#pragma once

#include <string>
#include <string_view>

namespace Lunasm {

class Lexer
{
public:
    Lexer(const std::string&);

private:
    char eat();
    void step();
    void skip(std::size_t);
    void skip(const std::string&);

    char current_char() const;

private:
    bool is_empty() const;

private:
    std::size_t m_line;
    std::size_t m_index;
    std::string m_source_code;
};

}  // namespace Lunasm
