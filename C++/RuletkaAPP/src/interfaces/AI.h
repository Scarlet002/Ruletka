#pragma once
#include <cstdint>

class AI
{
protected:
    AI() = default;
public:
    AI(const AI&) = delete;
    AI& operator=(const AI&) = delete;

    AI(AI&&) = delete;
    AI& operator=(AI&&) = delete;

    [[nodiscard]] virtual int8_t Decision() const = 0;

    virtual ~AI() = default;
};
