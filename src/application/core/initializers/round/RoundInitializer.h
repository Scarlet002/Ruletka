#pragma once

#include "Initializer.h"

class Inventory;
class Magazine;

class RoundInitializer final : public Initializer
{
private:
    Inventory& m_computerInventory;
    Inventory& m_humanInventory;
    Magazine& m_magazine;

public:
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    RoundInitializer(Inventory& computerInventory, Inventory& humanInventory, Magazine& magazine);

    auto Initialize() -> void override;
};
