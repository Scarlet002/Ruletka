#include "Player.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "HP.h"
#include "Inventory.h"
#include <string_view>
#include <utility>

Player::Player(std::string_view name, HP hitPoints, Inventory inventory, GameEnums::PlayerType type)
    : m_name(name), m_hp(hitPoints), m_inventory(std::move(inventory)), m_type(type)
{
}

auto Player::GetInventory() noexcept -> Inventory&
{
    return m_inventory;
}

auto Player::GetHP() noexcept -> HP&
{
    return m_hp;
}

auto Player::GetInventory() const noexcept -> const Inventory&
{
    return m_inventory;
}

auto Player::GetHP() const noexcept -> const HP&
{
    return m_hp;
}

auto Player::IsAlive() const noexcept -> GameEnums::YesNo
{
    return m_hp.GetHP() > GameConfig::MIN_PLAYER_HP ? GameEnums::YesNo::YES : GameEnums::YesNo::NO;
}

auto Player::GetType() const noexcept -> GameEnums::PlayerType
{
    return m_type;
}

auto Player::GetTypeString() const noexcept -> std::string_view
{
    return m_type == GameEnums::PlayerType::HUMAN ? "human" : "computer";
}

auto Player::GetName() const noexcept -> std::string_view
{
    return m_name;
}

void Player::SetName(std::string_view newName)
{
    m_name = newName;
}

void Player::SetType(GameEnums::PlayerType newType) noexcept
{
    m_type = newType;
}
