#pragma once
#include "ForwardDeclarations.h"
#include <string>

class IPlayer
{
protected:
    IPlayer() = default;
public:
    IPlayer(const IPlayer&) = delete;
    IPlayer& operator=(const IPlayer&) = delete;

    IPlayer(IPlayer&&) = delete;
	IPlayer& operator=(IPlayer&&) = delete;

    [[nodiscard]] virtual IInventory& GetInventory() noexcept = 0;
    [[nodiscard]] virtual HP& GetHP() noexcept = 0;

    virtual void SetName(const std::string& newName) = 0;
    virtual void SetType(const std::string& newType) = 0;

    [[nodiscard]] virtual bool IsAlive() const noexcept = 0;
    [[nodiscard]] virtual bool GetType() const noexcept = 0;
	[[nodiscard]] virtual std::string GetTypeString() const noexcept = 0;
    [[nodiscard]] virtual std::string GetName() const noexcept = 0;

    virtual ~IPlayer() = default;
};