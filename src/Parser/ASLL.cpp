#include <variant>

#include "fmt/core.h"
#include "fmt/ranges.h"

#include "Parser/ASLL.hpp"
#include "Parser/Instruction.hpp"

namespace Lunasm {

ASLL::ASLL()
    : m_index(0)
{}

ASLL::ASLL(const std::vector<Inst>& instructions)
    : m_index(0)
    , m_instructions(instructions)
{}

void ASLL::resolve_labels()
{
    for (auto& i : m_instructions)
    {
        std::visit(
            [&](auto& arg) -> void {
                using T = std::remove_reference_t<decltype(arg)>;

                if constexpr (std::is_same_v<T, Instruction>)
                {
                    m_index += arg.size();
                }
                else if constexpr (std::is_same_v<T, Label>)
                {
                    auto label = arg.label();

                    if (m_labels.find(label) == m_labels.end())
                    {
                        m_labels[label] = m_index;
                    }
                }
            },
            i);
    }
}

void ASLL::generate(std::string const& path)
{
    resolve_labels();

    for (auto& i : m_instructions)
    {

        std::visit([&](auto& arg) { arg.eval(m_output, m_labels); }, i);
    }

    fmt::print("{::#02x} \n", m_output);
}

void ASLL::handle_instructions(const std::vector<Inst>& instructions)
{
    m_instructions = instructions;
    generate("teste");
}

} // namespace Lunasm
