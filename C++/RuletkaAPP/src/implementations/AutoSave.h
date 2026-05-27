#pragma once
#include "ForwardDeclarations.h"
#include "AsyncSerializer.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "Logger.h"
#include "Action.h"
#include <string>
#include <memory>

class AutoSave : public Action
{
private:
    std::shared_ptr<IGameState> gs;
    std::shared_ptr<Logger> logger;
    std::shared_ptr<AsyncSerializer> as;
public:
    AutoSave(std::shared_ptr<IGameState> gs
        , std::shared_ptr<Logger> logger
        , std::shared_ptr<AsyncSerializer> as)
        : gs(gs)
        , logger(logger)
        , as(as) {}

    void Execute() override
    {
        std::string logLine = "";
        if (!as->IsSaving())
        {
            as->SaveGameStateAsync(gs);
            if (as->GetSerializationLog() != "")
            {
                logLine = as->GetSerializationLog();
            }
            else { logLine = "Wykonano zapis: autosave" + std::to_string(as->GetSaveCounter()); }
            logger->UpdateLog(logLine);
        }
    }
};