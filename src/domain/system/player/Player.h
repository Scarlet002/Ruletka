#pragma once

#include "GameConfig.h"
#include "GameEnums.h"
#include "HP.h"
#include "Inventory.h"
#include <boost/static_string/static_string.hpp>
#include <string_view>

class Player final
{
private:
    boost::static_string<GameConfig::MAX_FILENAME_LENGTH> m_name;
    HP m_hp;
    Inventory m_inventory;
    GameEnums::PlayerType m_type = GameEnums::PlayerType::HUMAN;

public:
    Player(std::string_view name, HP hitPoints, Inventory inventory, GameEnums::PlayerType type);

    [[nodiscard]]
    auto GetInventory() const noexcept -> const Inventory&;
    [[nodiscard]]
    auto GetHP() const noexcept -> const HP&;
    [[nodiscard]]
    auto GetInventory() noexcept -> Inventory&;
    [[nodiscard]]
    auto GetHP() noexcept -> HP&;
    [[nodiscard]]
    auto IsAlive() const noexcept -> GameEnums::YesNo;
    [[nodiscard]]
    auto GetType() const noexcept -> GameEnums::PlayerType;
    [[nodiscard]]
    auto GetTypeString() const noexcept -> std::string_view;
    [[nodiscard]]
    auto GetName() const noexcept -> std::string_view;

    auto SetName(std::string_view newName) -> void;
    auto SetType(GameEnums::PlayerType newType) noexcept -> void;
};
