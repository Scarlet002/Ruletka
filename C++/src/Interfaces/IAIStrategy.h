#pragma once

class IAIStrategy
{
public:
    virtual int MakeDecision() const = 0;

    virtual ~IAIStrategy() = default;
};
