#pragma once
#include "IGameState.h"

class AsyncSerializer
{
protected:
	AsyncSerializer() = default;
public:
    AsyncSerializer(const AsyncSerializer&) = delete;
    AsyncSerializer& operator=(const AsyncSerializer&) = delete;

    AsyncSerializer(AsyncSerializer&&) = delete;
    AsyncSerializer& operator=(AsyncSerializer&&) = delete;

    virtual void SetSaveCounter(uint8_t newSaveCounter) = 0;

    [[nodiscard]] virtual uint8_t GetSaveCounter() const noexcept = 0;

    virtual void SaveGameStateAsync(const std::shared_ptr<IGameState> gs) = 0;

    [[nodiscard]] virtual bool IsSaving() const noexcept = 0;

    [[nodiscard]] virtual std::string GetSerializationLog() const noexcept = 0;

    virtual ~AsyncSerializer() = default;
};
