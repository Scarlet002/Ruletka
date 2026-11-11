#pragma once

#include "GameConfig.h"
#include "GameEnums.h"
#include <array>
#include <cstdint>
#include <span>

struct MagazineView final
{
    std::span<const GameEnums::MagazineChamber, GameConfig::MAX_BULLETS> m_magazine;
    uint8_t m_head = GameConfig::MIN_BULLETS;
};

class Magazine final
{
private:
    std::array<GameEnums::MagazineChamber, GameConfig::MAX_BULLETS> m_magazine = {};
    double m_hitProbability = 0.0;
    uint8_t m_head = GameConfig::MIN_BULLETS;

public:
    [[nodiscard]]
    auto GetBullets(GameEnums::MagazineChamber type) const -> uint8_t;
    auto Reload() -> void;
    [[nodiscard]]
    auto IsEmpty() const noexcept -> bool;
    [[nodiscard]]
    auto GetMagazine() const noexcept -> MagazineView;
    auto SetMagazine(MagazineView newMagazine) -> void;
    auto InvertBulletType() -> void;
    [[nodiscard]]
    auto GetMagazineSize() const noexcept -> uint8_t;
    [[nodiscard]]
    auto CheckMagazineChamber(uint8_t index) const -> GameEnums::MagazineChamber;
    [[nodiscard]]
    auto GetHitProbability() const noexcept -> double;
    auto DecreaseBulletCount() -> void;
    auto SetHitProbability(double newProbability) noexcept -> void;
    auto CalculateHitProbability() -> void;
};
