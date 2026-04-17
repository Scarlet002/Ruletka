#pragma once
#include <cstdint>

class IAIStrategy
{
public:
    virtual int8_t Decision() const = 0;

    virtual ~IAIStrategy() = default;
};
