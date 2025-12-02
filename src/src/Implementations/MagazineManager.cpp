#pragma once
#include "GameEnums.h"
#include "MagazineManager.h"
#include <iostream>
#include <vector>
#include <stdexcept>

using std::cout;
using std::endl;
using std::runtime_error;
using std::any_of;

void MagazineManager::Load()
{
    bulletCount = rand() % 8 + 1;
    magazine.resize(bulletCount);

    for (int i = 0; i < bulletCount; i++)
    {
        magazine[i] = rand() % 2;
    }
}

void MagazineManager::ShowBullets() const
{
    for (int i = 0; i < bulletCount; i++)
    {
        if (magazine[i] == 1)
            cout << "Pelna - 1" << endl;
        else
            cout << "Pusta - 0" << endl;
    }
}

bool MagazineManager::CheckBulletType() const
{
    return magazine[0] == GameEnums::FULL;
}

void MagazineManager::CheckBullets()
{
    for (int i = 0; i < bulletCount; i++)
    {
        if (magazine[i] == 1)
            full++;
        else
            empty++;
    }
}

int MagazineManager::ShowFull() const { return full; }
int MagazineManager::ShowEmpty() const { return empty; }

void MagazineManager::DecreaseFullCount() { if (full > 0) full--; }
void MagazineManager::DecreaseEmptyCount() { if (empty > 0) empty--; }

int MagazineManager::ShowBulletCount() const { return static_cast<int>(magazine.size()); }

void MagazineManager::SetBulletCount(int newBulletCount)
{
    bulletCount = newBulletCount;
    magazine.resize(bulletCount);
}

void MagazineManager::SetFull(int newFull) { full = newFull; }
void MagazineManager::SetEmpty(int newEmpty) { empty = newEmpty; }

void MagazineManager::DecreaseBulletCount()
{
    if (bulletCount == 0) return;
    magazine.erase(magazine.begin());
    bulletCount = static_cast<int>(magazine.size());
}

bool MagazineManager::IsOutOfBullets() const { return IsEmpty(); }

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
    if (magazine.empty()) throw runtime_error("Magazynek jest pusty!");
    return magazine[0] == GameEnums::EMPTY;
}

bool MagazineManager::IsEmpty() const { return bulletCount == 0; }

const vector<int>& MagazineManager::GetMagazine() const { return magazine; }

void MagazineManager::SetMagazine(const vector<int>& newMagazine)
{
    magazine = newMagazine;
    bulletCount = static_cast<int>(magazine.size());
}

double MagazineManager::CalculateHitProbability() const
{
    if (magazine.empty()) return 0.0;
    return static_cast<double>(full) / bulletCount;
}

bool MagazineManager::HasEmptyBullets() const
{
    return any_of(magazine.begin(), magazine.end(), [](int bullet) { return bullet == GameEnums::EMPTY; });
}
