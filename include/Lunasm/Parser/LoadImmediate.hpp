#pragma once

#include <memory>

#include "Node.hpp"
#include "Register.hpp"
#include "Immediate.hpp"

namespace Lunasm {

class LoadImmediate : public Node
{
public:
    LoadImmediate(std::size_t, std::uint8_t, Register, Immediate);

    virtual void print() override;
    virtual std::uint8_t eval() override;
    virtual std::size_t size() const override;

private:
    std::size_t m_size;
    std::uint8_t m_output;
    Register m_register;
    Immediate m_immediate;
};

}  // namespace Lunasm
