#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "Parser/Instruction.hpp"
#include "Parser/Label.hpp"

namespace Lunasm {

using Inst = std::variant<Instruction, Label>;

class ASL
{
public:
    ASL();
    ASL(const std::vector<Inst>& instructions);

    void resolve_labels();
    void generate(std::string const& path);
    void handle_instructions(const std::vector<Inst>& instructions);

private:
    std::size_t m_index;
    std::vector<Inst> m_instructions;
    std::vector<std::uint8_t> m_output;
    std::unordered_map<std::string_view, std::uint16_t> m_labels;
};

} // namespace Lunasm
