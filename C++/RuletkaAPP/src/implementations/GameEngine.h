#pragma once
#include "ForwardDeclarations.h"
#include "SerializationManager.h"
#include "Logger.h"
#include "IGameState.h"
#include "AIManager.h"
#include "Processor.h"
#include "IGameEngine.h"
#include "GameConfig.h"
#include "Initializer.h"
#include "GameLoopState.h"
#include "Validator.h"
#include "UI.h"
#include <string>
#include <memory>
#include <utility>
#include <thread>
#include <chrono>

class GameEngine : public IGameEngine
{
private:
    std::shared_ptr<IGameState> gs;
    std::shared_ptr<Processor> processor;
    std::shared_ptr<UI> ui;
    std::shared_ptr<Validator> glv;
public:
    explicit GameEngine(
        std::shared_ptr<IGameState> gs
        , std::shared_ptr<UI> ui
        , std::shared_ptr<Processor> processor
        , std::shared_ptr<Validator> glv)
        : ui(std::move(ui))
        , processor(std::move(processor))
        , gs(std::move(gs))
        , glv(std::move(glv)) {}

    void RunLoop() override
    {
        do
        {
            // Pomiar czasu trwania jednej iteracji pêtli

            /*auto start = std::chrono::high_resolution_clock::now();*/

            ui->Render();

            processor->Process();

            glv->Validate();

            std::this_thread::sleep_for(std::chrono::milliseconds(16));

            /*auto end = std::chrono::high_resolution_clock::now();
            auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            std::cout << "Loop time: " << duration_us << " us" << std::endl;*/

        } while (gs->GetGameLoopState().GetStateOfGameLoop());
    }
};