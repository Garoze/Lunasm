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
    void parse_file(std::filesystem::path const&, bool = false);

private:
    void step();
    std::optional<Token> look_ahead(std::size_t);

private:
    bool parse_label();
    std::uint8_t parse_register();
    std::uint16_t parse_address();
    std::uint16_t parse_immediate();

    void parse_modes();

private:
    void nop_instruction();

    void mov_instruction();

    void shl_instruction();
    void shr_instruction();

    void and_instruction();
    void bor_instruction();
    void xor_instruction();
    void not_instruction();

    void psh_instruction();
    void pop_instruction();

    void inc_instruction();
    void dec_instruction();

    void add_instruction();
    void sub_instruction();
    void mul_instruction();
    void div_instruction();
    void mod_instruction();

    void cmp_instruction();

    void jmp_instruction();
    void jeq_instruction();
    void jne_instruction();

    void jsr_instruction();
    void ret_instruction();

    void hlt_instruction();

private:
    Token expect(TokenKind);

    template <typename... Kinds>
    bool expect_any(Kinds... kinds);

private:
    std::size_t m_index;
    std::vector<Token> m_tokens;
    std::unique_ptr<Lexer> m_lexer;
};

}  // namespace Lunasm
