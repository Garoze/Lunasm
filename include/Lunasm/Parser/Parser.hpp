#pragma once

#include <memory>
#include <vector>
#include <optional>
#include <algorithm>
#include <filesystem>

#include "Lexer/Lexer.hpp"
#include "Lexer/Token.hpp"

namespace Lunasm {

class Parser
{
public:
    Parser();

    void Parse();
    void parse_file(std::filesystem::path const&);

private:
    void step();
    void skip(const std::string&);
    std::optional<Token> look_ahead(std::size_t);

private:
    bool parse_immediate();
    bool parse_address();
    bool parse_register();

private:
    void nop_instruction();

    void mov_instruction();

    void shl_instruction();
    void shr_instruction();

    void and_instruction();
    void bor_instruction();
    void xor_instruction();
    void not_instruction();

private:
    bool expect(TokenKind);

    template <typename... Kinds>
    bool expect_any(Kinds... kinds);

private:
    std::size_t m_index;
    std::vector<Token> m_tokens;
    std::unique_ptr<Lexer> m_lexer;
};

}  // namespace Lunasm
