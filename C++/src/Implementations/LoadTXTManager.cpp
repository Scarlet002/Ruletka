#include "LoadTXTManager.h"
#include "SaveConfig.h"
#include "GameState.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdint>

void LoadTXTManager::LoadGameState(GameState& state,
    const std::string& fileName)
{
    std::string saveDir;
    if (fileName.find("autosave") == 0) { saveDir = SaveConfig::GetAutoSaveDirectory(); }
    else { saveDir = SaveConfig::GetSaveDirectory(); }
    std::string fullPath = saveDir + "/" + fileName;
    std::ifstream gameSave(fullPath);
    if (!gameSave.is_open())
        { throw std::runtime_error("Nie mozna otworzyc pliku podczas wczytywania!"); }

    uint8_t bullet, hpHuman, itemsHuman, sawsHuman,
        beersHuman, magnifiersHuman, invertersHuman,
        handCuffsHuman, cellPhonesHuman, hpComputer,
        itemsComputer, sawsComputer, beersComputer,
        magnifiersComputer, invertersComputer,
        handCuffsComputer, cellPhonesComputer,
        full, empty, bulletCount, starter,
        difficulty, choice, shooter, target,
        item, itemHuman, itemComputer, damage;

    bool wereHandCuffsUsed,
        wasCellPhoneUsed,
        wasMagnifierUsed,
        wasInventoryShownForComputer;

    gameSave >> hpHuman >> itemsHuman;

    state.human->SetHP(hpHuman);
    std::vector<uint8_t> humanInventory;
    for (uint8_t i = 0; i < itemsHuman; ++i)
    {
        gameSave >> itemHuman;
        humanInventory.push_back(itemHuman);
    }
    state.human->SetInventory(humanInventory);

    gameSave >> sawsHuman >> beersHuman >>
        magnifiersHuman >> invertersHuman >>
        handCuffsHuman >> cellPhonesHuman;

    state.human->SetSaws(sawsHuman);
    state.human->SetBeers(beersHuman);
    state.human->SetMagnifiers(magnifiersHuman);
    state.human->SetInverters(invertersHuman);
    state.human->SetHandCuffs(handCuffsHuman);
    state.human->SetCellPhones(cellPhonesHuman);

    gameSave >> hpComputer >> itemsComputer;

    state.computer->SetHP(hpComputer);
    std::vector<uint8_t> computerInventory;
    for (uint8_t i = 0; i < itemsComputer; ++i)
    {
        gameSave >> itemComputer;
        computerInventory.push_back(itemComputer);
    }
    state.computer->SetInventory(computerInventory);

    gameSave >> sawsComputer >> beersComputer >>
        magnifiersComputer >> invertersComputer >>
        handCuffsComputer >> cellPhonesComputer;

    state.computer->SetSaws(sawsComputer);
    state.computer->SetBeers(beersComputer);
    state.computer->SetMagnifiers(magnifiersComputer);
    state.computer->SetInverters(invertersComputer);
    state.computer->SetHandCuffs(handCuffsComputer);
    state.computer->SetCellPhones(cellPhonesComputer);

	gameSave >> full >> empty >> bulletCount;

    state.magazine->SetFull(full);
    state.magazine->SetEmpty(empty);
    state.magazine->SetBulletCount(bulletCount);
    std::vector<uint8_t> magazine;
    for (uint8_t i = 0; i < bulletCount; ++i)
    {
        gameSave >> bullet;
        magazine.push_back(bullet);
    }
    state.magazine->SetMagazine(magazine);

    gameSave >> starter >>
        difficulty >> choice >>
        shooter >> target >>
        item >> damage >>
        wereHandCuffsUsed >>
        wasCellPhoneUsed >>
        wasMagnifierUsed >>
        wasInventoryShownForComputer;

    state.turn->SetStarter(starter);
    state.turn->SetDifficulty(difficulty);
    state.turn->SetChoice(choice);
    state.turn->SetShooter(shooter);
    state.turn->SetTarget(target);
    state.turn->SetItem(item);
    state.turn->SetDamage(damage);
    state.turn->SetStateOfHandCuffs(wereHandCuffsUsed);
    state.turn->SetStateOfCellPhone(wasCellPhoneUsed);
    state.turn->SetStateOfMagnifier(wasMagnifierUsed);
    state.turn->SetStateOfInventory(wasInventoryShownForComputer);
}