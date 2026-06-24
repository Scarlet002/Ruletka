#pragma once
#include "ForwardDeclarations.h"
#include "GameLoopState.h"
#include "ItemState.h"
#include "DecisionState.h"
#include "IPlayer.h"
#include "Magazine.h"
#include "Player.h"
#include "HPManager.h"
#include "Inventory.h"
#include "ShotgunMagazine.h"
#include "IInventory.h"
#include "HP.h"
#include "SerializationState.h"
#include "AIState.h"
#include "IGameState.h"
#include <memory>
#include <utility>

class GameState : public IGameState
{
private:
    std::shared_ptr<IPlayer> human;
    std::shared_ptr<IPlayer> computer;
    std::shared_ptr<Magazine> magazine;
    std::shared_ptr<GameLoopState> gls;
    std::shared_ptr<ItemState> is;
    std::shared_ptr<AIState> ais;
    std::shared_ptr<DecisionState> ds;
    std::shared_ptr<SerializationState> ss;

    void CopyHuman(const IGameState& snapshot)
    {
        human->SetName(snapshot.GetHuman().GetName());
        human->SetType(snapshot.GetHuman().GetTypeString());
        human->GetHP().SetHP(snapshot.GetHumanHP().GetHP());
        human->GetInventory().SetItemCount(GameEnums::SAW, snapshot.GetHumanInventory().GetItemCount(GameEnums::SAW));
        human->GetInventory().SetItemCount(GameEnums::BEER, snapshot.GetHumanInventory().GetItemCount(GameEnums::BEER));
        human->GetInventory().SetItemCount(GameEnums::MAGNIFIER, snapshot.GetHumanInventory().GetItemCount(GameEnums::MAGNIFIER));
        human->GetInventory().SetItemCount(GameEnums::CELLPHONE, snapshot.GetHumanInventory().GetItemCount(GameEnums::CELLPHONE));
        human->GetInventory().SetItemCount(GameEnums::HANDCUFFS, snapshot.GetHumanInventory().GetItemCount(GameEnums::HANDCUFFS));
        human->GetInventory().SetItemCount(GameEnums::INVERTER, snapshot.GetHumanInventory().GetItemCount(GameEnums::INVERTER));
    }

    void CopyComputer(const IGameState& snapshot)
    {
        computer->SetName(snapshot.GetComputer().GetName());
        computer->SetType(snapshot.GetComputer().GetTypeString());
        computer->GetHP().SetHP(snapshot.GetComputerHP().GetHP());
        computer->GetInventory().SetItemCount(GameEnums::SAW, snapshot.GetComputerInventory().GetItemCount(GameEnums::SAW));
        computer->GetInventory().SetItemCount(GameEnums::BEER, snapshot.GetComputerInventory().GetItemCount(GameEnums::BEER));
        computer->GetInventory().SetItemCount(GameEnums::MAGNIFIER, snapshot.GetComputerInventory().GetItemCount(GameEnums::MAGNIFIER));
        computer->GetInventory().SetItemCount(GameEnums::CELLPHONE, snapshot.GetComputerInventory().GetItemCount(GameEnums::CELLPHONE));
        computer->GetInventory().SetItemCount(GameEnums::HANDCUFFS, snapshot.GetComputerInventory().GetItemCount(GameEnums::HANDCUFFS));
        computer->GetInventory().SetItemCount(GameEnums::INVERTER, snapshot.GetComputerInventory().GetItemCount(GameEnums::INVERTER));
    }

    void CopyMagazine(const IGameState& snapshot)
    {
        magazine->SetHitProbability(snapshot.GetMagazine().GetHitProbability());
        magazine->SetMagazine(snapshot.GetMagazine().GetMagazine());
        magazine->CheckBullets();
    }

    void CopySerializationState(const IGameState& snapshot)
    {
        ss->SetSerializationType(snapshot.GetSerializationState().GetSerializationType());
    }

    void CopyAIState(const IGameState& snapshot)
    {
        ais->SetDifficulty(snapshot.GetAIState().GetDifficulty());
        ais->SetRecentDifficulty(snapshot.GetAIState().GetRecentDifficulty());
    }

    void CopyDecisionState(const IGameState& snapshot)
    {
        ds->SetChoice(snapshot.GetDecisionState().GetChoice());
        ds->SetPreviousChoice(snapshot.GetDecisionState().GetPreviousChoice());
        ds->SetCurrentMenu(snapshot.GetDecisionState().GetCurrentMenu());
    }

    void CopyItemState(const IGameState& snapshot)
    {
        is->SetDamage(snapshot.GetItemState().GetDamage());
        is->SetStateOfHandCuffs(snapshot.GetItemState().GetStateOfHandCuffs());
        is->SetStateOfMagnifier(snapshot.GetItemState().GetStateOfMagnifier());
        is->SetStateOfCellPhone(snapshot.GetItemState().GetStateOfCellPhone());
    }

    void CopyGameLoopState(const IGameState& snapshot)
    {
        gls->SetStarter(snapshot.GetGameLoopState().GetStarter());
        gls->SetIsOnePlayerAlive(snapshot.GetGameLoopState().GetIsOnePlayerAlive());
        gls->SetStateOfGameLoop(snapshot.GetGameLoopState().GetStateOfGameLoop());
    }

    void CopyFrom(const IGameState& snapshot)
    {
        CopyAIState(snapshot);
        CopyItemState(snapshot);
        CopyDecisionState(snapshot);
        CopyGameLoopState(snapshot);
        CopySerializationState(snapshot);
        CopyHuman(snapshot);
        CopyComputer(snapshot);
        CopyMagazine(snapshot);
    }

public:
    explicit GameState(std::shared_ptr<IPlayer> human
        , std::shared_ptr<IPlayer> computer
        , std::shared_ptr<Magazine> magazine
        , std::shared_ptr<GameLoopState> gls
        , std::shared_ptr<ItemState> is
        , std::shared_ptr<AIState> ais
        , std::shared_ptr<DecisionState> ds
        , std::shared_ptr<SerializationState> ss)
        : human(std::move(human))
        , computer(std::move(computer))
        , magazine(std::move(magazine))
        , gls(std::move(gls))
        , is(std::move(is))
        , ais(std::move(ais))
        , ds(std::move(ds))
        , ss(std::move(ss)) {}

    std::shared_ptr<IGameState> CreateSnapshot() const  override
    {
        std::shared_ptr<GameState> snapshot = std::make_shared<GameState>(
            std::make_shared<Player>
            (std::make_shared <HPManager>()
                , std::make_shared <Inventory>()
                , "Human", "human"),
            std::make_shared<Player>
            (std::make_shared <HPManager>()
                , std::make_shared <Inventory>()
                , "Computer", "computer"),
            std::make_shared<ShotgunMagazine>(),
            std::make_shared<GameLoopState>(),
            std::make_shared<ItemState>(),
            std::make_shared<AIState>(),
            std::make_shared<DecisionState>(),
            std::make_shared<SerializationState>()
        );
        snapshot->CopyFrom(*this);
        return snapshot;
    }

    // Non-const getters
    IPlayer& GetHuman() noexcept override { return *human; }
    IInventory& GetHumanInventory() noexcept override { return human->GetInventory(); }
    HP& GetHumanHP() noexcept override { return human->GetHP(); }
    IPlayer& GetComputer() noexcept override { return *computer; }
    IInventory& GetComputerInventory() noexcept override { return computer->GetInventory(); }
    HP& GetComputerHP() noexcept override { return computer->GetHP(); }
    Magazine& GetMagazine() noexcept override { return *magazine; }
    GameLoopState& GetGameLoopState() noexcept override { return *gls; }
    ItemState& GetItemState() noexcept override { return *is; }
    AIState& GetAIState() noexcept override { return *ais; }
    DecisionState& GetDecisionState() noexcept override { return *ds; }
    SerializationState& GetSerializationState() noexcept override { return *ss; }

    // Const getters
    const IPlayer& GetHuman() const noexcept override { return *human; }
    const IInventory& GetHumanInventory() const noexcept { return human->GetInventory(); }
    const HP& GetHumanHP() const noexcept { return human->GetHP(); }
    const IPlayer& GetComputer() const noexcept override { return *computer; }
    const IInventory& GetComputerInventory() const noexcept { return computer->GetInventory(); }
    const HP& GetComputerHP() const noexcept { return computer->GetHP(); }
    const Magazine& GetMagazine() const noexcept override { return *magazine; }
    const GameLoopState& GetGameLoopState() const noexcept override { return *gls; }
    const ItemState& GetItemState() const noexcept override { return *is; }
    const AIState& GetAIState() const noexcept override { return *ais; }
    const DecisionState& GetDecisionState() const noexcept override { return *ds; }
    const SerializationState& GetSerializationState() const noexcept override { return *ss; }
};