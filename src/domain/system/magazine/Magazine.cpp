#include "Magazine.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "RNG.h"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <utility>

auto Magazine::CalculateHitProbability() -> void
{
    const auto blank = GetBullets(GameEnums::MagazineChamber::BLANK);
    const auto live = GetBullets(GameEnums::MagazineChamber::LIVE);
    const auto total = blank + live;
    m_hitProbability = (total == 0) ? 0.0 : static_cast<double>(live) / total;
}

auto Magazine::SetHitProbability(double newProbability) noexcept -> void
{
    m_hitProbability = newProbability;
}

auto Magazine::DecreaseBulletCount() -> void
{
    if (m_head >= GameConfig::MAX_BULLETS)
    {
        return;
    }
    m_magazine[m_head] = GameEnums::MagazineChamber::EMPTY;
    CalculateHitProbability();
    ++m_head;
}

auto Magazine::Reload() -> void
{
    using GameEnums::MagazineChamber;
    using namespace GameConfig;
    m_hitProbability = MIN_PROBABILITY;
    m_head = MIN_BULLETS;
    for (auto& bullet : m_magazine)
    {
        bullet = MagazineChamber::EMPTY;
    }

    constexpr auto BLANK_INT = std::to_underlying(MagazineChamber::BLANK);
    constexpr auto LIVE_INT = std::to_underlying(MagazineChamber::LIVE);
    const auto newSize = RNG::GetRN(MIN_BULLETS_RNG, MAX_BULLETS_RNG);
    for (auto bullet = GameConfig::MIN_BULLETS; bullet < newSize; ++bullet)
    {
        m_magazine[bullet] = static_cast<GameEnums::MagazineChamber>(RNG::GetRN<uint8_t>(BLANK_INT, LIVE_INT));
    }
}

auto Magazine::SetMagazine(MagazineView newMagazine) -> void
{
    if (newMagazine.m_head >= GameConfig::MAX_BULLETS)
    {
        throw std::out_of_range("Invalid magazine head index!");
    }
    std::ranges::copy(newMagazine.m_magazine, m_magazine.begin());
    m_head = newMagazine.m_head;
}

auto Magazine::GetHitProbability() const noexcept -> double
{
    return m_hitProbability;
}

auto Magazine::GetBullets(GameEnums::MagazineChamber type) const -> uint8_t
{
    return static_cast<uint8_t>(
        std::count_if(m_magazine.begin(), m_magazine.end(),
                      [type](GameEnums::MagazineChamber bullet) -> bool { return bullet == type; }));
}

auto Magazine::InvertBulletType() -> void
{
    if (IsEmpty())
    {
        return;
    }

    using namespace GameConfig;
    using GameEnums::MagazineChamber;
    switch (CheckMagazineChamber(m_head))
    {
    case MagazineChamber::BLANK:
        m_magazine[m_head] = MagazineChamber::LIVE;
        break;
    case MagazineChamber::LIVE:
        m_magazine[m_head] = MagazineChamber::BLANK;
        break;
    default:
    case MagazineChamber::EMPTY:
        break;
    }
}

auto Magazine::GetMagazineSize() const noexcept -> uint8_t
{
    const auto blank = GetBullets(GameEnums::MagazineChamber::BLANK);
    const auto live = GetBullets(GameEnums::MagazineChamber::LIVE);
    const auto total = blank + live;
    return static_cast<uint8_t>(total);
}

auto Magazine::CheckMagazineChamber(uint8_t index) const -> GameEnums::MagazineChamber
{
    if (index >= GameConfig::MAX_BULLETS)
    {
        throw std::out_of_range("Index is out of range!");
    }

    return m_magazine[index];
}

auto Magazine::IsEmpty() const noexcept -> bool
{
    return GetBullets(GameEnums::MagazineChamber::EMPTY) == GameConfig::MAX_BULLETS;
}

auto Magazine::GetMagazine() const noexcept -> MagazineView
{
    return {.m_magazine = m_magazine, .m_head = m_head};
}
