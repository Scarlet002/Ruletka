#include "GameEnums.h"
#include "ShotgunMagazine.h"
#include "RNG.h"
#include <iostream>
#include <deque>
#include <stdexcept>
#include <cstdint>
#include <cassert>

ShotgunMagazine::ShotgunMagazine() : magazine() {}

void ShotgunMagazine::CheckBullets()
{
    ValidateMagazineSize();
    full = count_if(magazine.begin(), magazine.end(),
        [](uint8_t bullet) { return bullet == GameEnums::FULL; });
    empty = magazine.size() - full;
}

void ShotgunMagazine::DecreaseBulletCount()
{
    ValidateMagazineSize();
    magazine.pop_front();
}

void ShotgunMagazine::UpdateMagazineState(uint8_t bullet)
{
    if (CheckBulletType(bullet))
    {
        DecreaseFullCount();
    }
    else { DecreaseEmptyCount(); }
    DecreaseBulletCount();
}

void ShotgunMagazine::Reload()
{
    magazine.clear();
    uint8_t newSize = RNG::GetRN(GameConfig::minBulletsRNG, GameConfig::maxBulletsRNG);
    magazine.resize(newSize);
    for (uint8_t& bullet : magazine)
    {
        bullet = RNG::GetRN<uint8_t>(GameEnums::EMPTY, GameEnums::FULL);
    }
    CheckBullets();
}

void ShotgunMagazine::ValidateMagazineSize() const
{
    try
    {
        if (magazine.empty())
        {
            throw std::runtime_error("Magazynek jest pusty!");
        }
        if (magazine.size() > GameConfig::maxBullets)
        {
            throw std::runtime_error("Rozmiar magazynka przekracza maksymalna liczbe pociskow!");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void ShotgunMagazine::SetMagazine(const std::deque<uint8_t>& newMagazine)
{
    magazine = newMagazine;
    ValidateMagazineSize();
}

float ShotgunMagazine::CalculateHitProbability() const noexcept
{
    ValidateMagazineSize();
    uint8_t size = GetMagazineSize();
    if (size == 0) { return 0.f; }
    else { return static_cast<float>(full) / size; }
}

uint8_t ShotgunMagazine::GetFull() const noexcept { return full; }

uint8_t ShotgunMagazine::GetEmpty() const noexcept { return empty; }

void ShotgunMagazine::DecreaseFullCount() { if (full > 0) full--; }

void ShotgunMagazine::DecreaseEmptyCount() { if (empty > 0) empty--; }

void ShotgunMagazine::InvertBulletType() 
{ 
    ValidateMagazineSize();
    CheckBulletType(GameEnums::FIRST_BULLET) 
        ? magazine[GameEnums::FIRST_BULLET] = GameEnums::EMPTY 
        : magazine[GameEnums::FIRST_BULLET] = GameEnums::FULL;
}

uint8_t ShotgunMagazine::GetMagazineSize() const noexcept
{
    auto size = magazine.size();
    assert(size <= GameConfig::maxBullets);
    if (size > GameConfig::maxBullets) { return 0; }
    return static_cast<uint8_t>(size);
}

bool ShotgunMagazine::CheckBulletType(uint8_t bullet) const noexcept
{ 
    ValidateMagazineSize();
    try
    {
        if (bullet < magazine.size())
        {
            return magazine[bullet] == GameEnums::FULL;
        }
        throw std::out_of_range("Indeks pocisku poza zakresem!");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool ShotgunMagazine::IsEmpty() const noexcept { return GetMagazineSize() == 0; }

void ShotgunMagazine::SetHitProbability(float newProbability) { hitProbability = newProbability; }

float ShotgunMagazine::GetHitProbability() const noexcept { return hitProbability; }

const std::deque<uint8_t>& ShotgunMagazine::GetMagazine() const noexcept { return magazine; }