#include "RoundInitializer.h"
#include "Inventory.h"
#include "Magazine.h"

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
RoundInitializer::RoundInitializer(Inventory& computerInventory, Inventory& humanInventory, Magazine& magazine)
    : m_computerInventory(computerInventory), m_humanInventory(humanInventory), m_magazine(magazine)
{
}

void RoundInitializer::Initialize()
{
    m_magazine.Reload();
    m_humanInventory.GetRandomItems();
    m_computerInventory.GetRandomItems();
}
