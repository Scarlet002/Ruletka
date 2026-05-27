#pragma once
#include "Validator.h"
#include "IGameState.h"
#include "DecisionState.h"
#include "GameLoopState.h"
#include "IPlayer.h"
#include "Magazine.h"
#include "AsyncSerializer.h"
#include "Initializer.h"
#include "UI.h"
#include <memory>

class GameLoopValidator : public Validator
{
private:
    std::shared_ptr<IGameState> gs;
    std::shared_ptr<AsyncSerializer> as;
    std::shared_ptr<Initializer> gli;
    std::shared_ptr<Initializer> ri;
    std::shared_ptr<UI> ui;
public:
    GameLoopValidator(std::shared_ptr<IGameState> gs
        , std::shared_ptr<AsyncSerializer> as
        , std::shared_ptr<Initializer> gli
        , std::shared_ptr<Initializer> ri
        , std::shared_ptr<UI> ui)
        : gs(gs)
        , as(as)
        , gli(gli)
        , ri(ri)
        , ui(ui) {}

	void Validate() override
	{
        if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::RESTART_MENU
            && gs->GetDecisionState().GetChoice() == GameEnums::RESTART_YES)
        {
            ui->ResetUI();
            gli->Initialize();
            as->SetSaveCounter(0);
        }
        if (!gs->GetHuman().IsAlive() || !gs->GetComputer().IsAlive())
        {
            gs->GetGameLoopState().SetStarter(GameEnums::HUMAN);
            gs->GetDecisionState().SetChoice(GameEnums::NO_CHOICE);
            gs->GetDecisionState().SetCurrentMenu(GameEnums::RESTART_MENU);
            gs->GetGameLoopState().SetIsOnePlayerAlive(true);
            as->SetSaveCounter(0);
        }
        if (gs->GetMagazine().IsEmpty() && !gs->GetGameLoopState().GetIsOnePlayerAlive()) ri->Initialize();
	}
};