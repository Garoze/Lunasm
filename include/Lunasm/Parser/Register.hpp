#pragma once

#include "Node.hpp"

namespace Lunasm {


class Register : public Node
{
public:
    Register();

    virtual void print() override;
    virtual std::uint8_t eval() override;
    virtual std::size_t size() const override;

private:
};

}
