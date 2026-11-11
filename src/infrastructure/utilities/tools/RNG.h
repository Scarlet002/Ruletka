#pragma once

#include <cstdint>
#include <random>
#include <stdexcept>
#include <type_traits>

class RNG final
{
private:
    [[nodiscard]]
    static auto GetEngine() -> std::mt19937&
    {
        thread_local std::mt19937 engine(std::random_device{}());
        return engine;
    }

public:
    RNG() = delete;

    template <typename T>
        requires std::is_integral_v<T> && std::is_unsigned_v<T>
    [[nodiscard]]
    static auto GetRN(T lowerLimit, T upperLimit) -> T
    {
        if (lowerLimit > upperLimit)
        {
            throw std::invalid_argument("LowerLimit > UpperLimit!");
        }

        if (lowerLimit == upperLimit)
        {
            return lowerLimit;
        }

        return static_cast<T>(std::uniform_int_distribution<uint64_t>(static_cast<uint64_t>(lowerLimit),
                                                                      static_cast<uint64_t>(upperLimit))(GetEngine()));
    }
};
