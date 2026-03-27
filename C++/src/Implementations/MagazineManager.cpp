#include "GameEnums.h"
#include "MagazineManager.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdint>

MagazineManager::MagazineManager() 
    : magazine() 
    { magazine.reserve(GameConfig::maxBulletsCount); }

void MagazineManager::Load()
{
    bulletCount = rand() % GameConfig::maxBullets + GameConfig::minBullets;
    magazine.resize(bulletCount);

    for (uint8_t i = 0; i < bulletCount; ++i)
        { magazine[i] = rand() % GameConfig::numberOfBulletTypes; }
}
void MagazineManager::CheckBullets()
{
    full = count_if(magazine.begin(), magazine.end(),
        [](uint8_t bullet) { return bullet == GameEnums::FULL; });
    empty = magazine.size() - full;
}
void MagazineManager::DecreaseBulletCount()
{
    if (bulletCount == 0) { return; }
    magazine.erase(magazine.begin());
    bulletCount = magazine.size();
}
void MagazineManager::Reload()
{
    magazine.clear();
    bulletCount = 0;
    empty = 0;
    full = 0;
    Load();
    CheckBullets();
}
bool MagazineManager::IsEmptySlot() const
{
    if (magazine.empty()) throw std::runtime_error("Magazynek jest pusty!");
    return magazine[0] == GameEnums::EMPTY;
}
void MagazineManager::SetMagazine(const std::vector<uint8_t>& newMagazine)
{
    magazine = newMagazine;
    bulletCount = magazine.size();
}
double MagazineManager::CalculateHitProbability() const
{
    if (magazine.empty()) { return 0.0; }
    return static_cast<double>(full) / bulletCount;
}
bool MagazineManager::HasEmptyBullets() const 
{ return any_of(magazine.begin(), magazine.end(), [](uint8_t bullet)
    { return bullet == GameEnums::EMPTY; }); }
int MagazineManager::ShowFull() const { return full; }
int MagazineManager::ShowEmpty() const { return empty; }
void MagazineManager::DecreaseFullCount() { if (full > 0) full--; }
void MagazineManager::DecreaseEmptyCount() { if (empty > 0) empty--; }
bool MagazineManager::CheckBulletType() const { return !magazine.empty() && magazine[0] == GameEnums::FULL; }
void MagazineManager::InvertBulletType() { CheckBulletType() ? magazine[0] = GameEnums::EMPTY : magazine[0] = GameEnums::FULL; };
int MagazineManager::GetMagazineSize() const { return magazine.size(); }
bool MagazineManager::CheckBulletTypeCellPhone(int bullet) const { return magazine[bullet] == GameEnums::FULL; }
bool MagazineManager::IsEmpty() const { return bulletCount == 0; }
const std::vector<uint8_t>& MagazineManager::GetMagazine() const { return magazine; }
bool MagazineManager::IsOutOfBullets() const { return IsEmpty(); }
void MagazineManager::SetFull(int newFull) { full = newFull; }
void MagazineManager::SetEmpty(int newEmpty) { empty = newEmpty; }
void MagazineManager::SetBulletCount(int newBulletCount)
{
    bulletCount = newBulletCount;
    magazine.resize(bulletCount);
}

void MagazineManager::ShowBullets() const
{
    std::cout << "Magazynek: ";
    for (uint8_t bullet : magazine)
    {
        std::cout << (bullet == GameEnums::FULL ? "[F] " : "[E] ");
    }
    std::cout << '\n';
}

int MagazineManager::ShowBulletCount() const { return bulletCount; }