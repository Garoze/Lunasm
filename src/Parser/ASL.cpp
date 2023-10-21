#include <variant>

#include "fmt/core.h"
#include "fmt/ranges.h"

#include "Parser/ASL.hpp"
#include "Parser/Instruction.hpp"

namespace Lunasm {

ASL::ASL()
    : m_index(0)
{}

ASL::ASL(const std::vector<Inst>& instructions)
    : m_index(0)
    , m_instructions(instructions)
{}

void ASL::resolve_labels()
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

void ASL::generate(std::string const& path)
{
    resolve_labels();

    for (auto& i : m_instructions)
    {

        std::visit([&](auto& arg) { arg.eval(m_output, m_labels); }, i);
    }

    fmt::print("{::#02x} \n", m_output);
}

void ASL::handle_instructions(const std::vector<Inst>& instructions)
{
    m_instructions = instructions;
    generate("teste");
}

} // namespace Lunasm
