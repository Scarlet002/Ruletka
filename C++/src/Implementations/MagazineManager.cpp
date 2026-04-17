#include "GameEnums.h"
#include "MagazineManager.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdint>

MagazineManager::MagazineManager() 
    : magazine() 
    { magazine.reserve(GameConfig::maxBulletsCount); }

void MagazineManager::CheckBullets()
{
    ValidateMagazineSize();
    full = count_if(magazine.begin(), magazine.end(),
        [](uint8_t bullet) { return bullet == GameEnums::FULL; });
    empty = magazine.size() - full;
}

void MagazineManager::DecreaseBulletCount()
{
    ValidateMagazineSize();
    magazine.erase(magazine.begin());
}

void MagazineManager::UpdateMagazineState(uint8_t bullet)
{
    if (CheckBulletType(bullet))
    {
        DecreaseFullCount();
    }
    else { DecreaseEmptyCount(); }
    DecreaseBulletCount();
}

void MagazineManager::Reload()
{
    magazine.clear();
    uint8_t newSize = rand() % GameConfig::maxBullets + GameConfig::minBullets;
    magazine.resize(newSize);
    for (uint8_t& bullet : magazine)
    {
        bullet = rand() % GameConfig::numberOfBulletTypes;
    }
    CheckBullets();
}

void MagazineManager::ValidateMagazineSize() const
{
    if (magazine.empty())
    {
        throw std::runtime_error("Magazynek jest pusty!");
    }
    if (magazine.size() > GameConfig::maxBulletsCount)
    {
        throw std::runtime_error("Rozmiar magazynka przekracza maksymalna liczbe pociskow!");
	}
}

void MagazineManager::SetMagazine(const std::vector<uint8_t>& newMagazine)
{
    magazine = newMagazine;
    ValidateMagazineSize();
}

float MagazineManager::CalculateHitProbability() const
{
    ValidateMagazineSize();
    return static_cast<float>(full) / GetMagazineSize();
}

uint8_t MagazineManager::GetFull() const { return full; }

uint8_t MagazineManager::GetEmpty() const { return empty; }

void MagazineManager::DecreaseFullCount() { if (full > 0) full--; }

void MagazineManager::DecreaseEmptyCount() { if (empty > 0) empty--; }

void MagazineManager::InvertBulletType() 
{ 
    ValidateMagazineSize();
    CheckBulletType(GameEnums::LOADED) ? 
        magazine[GameEnums::LOADED] = GameEnums::EMPTY 
        : magazine[GameEnums::LOADED] = GameEnums::FULL;
}

uint8_t MagazineManager::GetMagazineSize() const { return magazine.size(); }

bool MagazineManager::CheckBulletType(uint8_t bullet) const 
{ 
    ValidateMagazineSize();
    if (bullet < magazine.size())
    {
        return magazine[bullet] == GameEnums::FULL;
    }
    throw std::out_of_range("Indeks pocisku poza zakresem!");
}

bool MagazineManager::IsEmpty() const { return GetMagazineSize() == 0; }

const std::vector<uint8_t>& MagazineManager::GetMagazine() const { return magazine; }