#pragma once
#include "ForwardDeclarations.h"
#include "IPlayer.h"
#include "HpManger.h"
#include "ShootingManager.h"
#include "DecisionManager.h"
#include "InventoryManager.h"
#include <string>
#include <memory>
#include <vector>

using std::string;
using std::vector;

class Player : public IPlayer
{
private:
    std::unique_ptr<DecisionManager> decision;
    std::unique_ptr<ShootingManager> gun;
    InventoryManager inventory;
    HpManager hp;
    string name;
    string type;

public:

    Player(const string& playerName, const string& playerType, GameConfig& gameConfig);

    void LoseHP(GameState& gameState) override;
    void RegainHP() override;
    void ResetHP() override;
    int GetHP() const override;
    void SetHP(int newHP) override;
    bool isAlive() const override;
    bool IsHuman() const override;
    bool IsComputer() const override;

    int SetFreeSlots(int newFree) override;
    int SetSaws(int newSaws) override;
    int SetBeers(int newBeers) override;
    int SetMagnifiers(int newMagnifiers) override;
    int SetHandCuffs(int newHandCuffs) override;
    int SetInverters(int newInverters) override;
    int SetCellPhones(int newCellPhones) override;
    void SetInventory(const vector<int>& newInventory) override;

    int GetFreeSlots() const override;
    int GetSaws() const override;
    int GetBeers() const override;
    int GetMagnifiers() const override;
    int GetHandCuffs() const override;
    int GetInverters() const override;
    int GetCellPhones() const override;
    const vector<int>& GetInventory() const override;

    int MakeDecision(GameState& gameState) const override;
    void Shoot(GameState& gameState) override;
    void GetRandomItem(GameState& gameState) override;
    void GetNumberOfItems(GameState& gameState) override;
    void ResetInventory(GameState& gameState) override;
    void UseSaw(GameState& gameState) override;
    void UseMagnifier(GameState& gameState) override;
    void UseBeer(GameState& gameState) override;
    void UseCellPhone(GameState& gameState) override;
    void UseInverter(GameState& gameState) override;
    void UseHandCuffs(GameState& gameState) override;

    ~Player() {};
};