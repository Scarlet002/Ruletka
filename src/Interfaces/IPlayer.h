#pragma once
#include "ForwardDeclarations.h"

class IPlayer
{
public:

    virtual void LoseHP(GameState& gameState) = 0;
    virtual void RegainHP() = 0;
    virtual void ResetHP() = 0;
    virtual int GetHP() const = 0;
    virtual void SetHP(int newHP) = 0;
    virtual bool isAlive() const = 0;
    virtual bool IsHuman() const = 0;
    virtual bool IsComputer() const = 0;

    virtual int SetFreeSlots(int newFree) = 0;
    virtual int SetSaws(int newSaws) = 0;
    virtual int SetBeers(int newBeers) = 0;
    virtual int SetMagnifiers(int newMagnifiers) = 0;
    virtual int SetHandCuffs(int newHandCuffs) = 0;
    virtual int SetInverters(int newInverters) = 0;
    virtual int SetCellPhones(int newCellPhones) = 0;

    virtual int GetFreeSlots() const = 0;
    virtual int GetSaws() const = 0;
    virtual int GetBeers() const = 0;
    virtual int GetMagnifiers() const = 0;
    virtual int GetHandCuffs() const = 0;
    virtual int GetInverters() const = 0;
    virtual int GetCellPhones() const = 0;

    virtual int MakeDecision(GameState& gameState) const = 0;
    virtual void Shoot(GameState& gameState) = 0;
    virtual void GetRandomItem(GameState& gameState) = 0;
    virtual void GetNumberOfItems(GameState& gameState) = 0;
    virtual void ResetInventory(GameState& gameState) = 0;
    virtual void UseSaw(GameState& gameState) = 0;
    virtual void UseMagnifier(GameState& gameState) = 0;
    virtual void UseBeer(GameState& gameState) = 0;
    virtual void UseCellPhone(GameState& gameState) = 0;
    virtual void UseInverter(GameState& gameState) = 0;
    virtual void UseHandCuffs(GameState& gameState) = 0;

    virtual ~IPlayer() = default;
};