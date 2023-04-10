#pragma once

#include "Node.hpp"

namespace Lunasm {

class Immediate : public Node
{
public:
    Immediate();

    virtual void print() override;
    virtual std::uint8_t eval() override;
    virtual std::size_t size() const override;

private:
};

}  // namespace Lunasm
