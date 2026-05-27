#pragma once
#include "ForwardDeclarations.h"
#include "AsyncSerializer.h"
#include "SerializationManager.h"
#include "IGameState.h"
#include <future>
#include <iostream>
#include <cstdint>
#include <string>
#include <atomic>
#include <memory>
#include <cassert>

class AutoSaveManager : public AsyncSerializer
{
private:
    std::future<void> saveFuture;
    std::shared_ptr<SerializationManager> serializer;
    std::atomic <uint8_t> saveCounter = 0;
    std::atomic<bool> isSaving = false;
public:
    explicit AutoSaveManager(std::shared_ptr<SerializationManager> serializer) : serializer(serializer) {}

    void SaveGameStateAsync(const std::shared_ptr<IGameState> gs) override
    {
        isSaving.store(true);
        saveCounter++;
        std::string autoSaveFileName = "autosave" + std::to_string(GetSaveCounter());
        std::shared_ptr<IGameState> snapshot = gs->CreateSnapshot();

        if (saveFuture.valid()) saveFuture.wait();
        saveFuture = std::async(std::launch::async, [this, snapshot, autoSaveFileName]()
        {
            try
            {
                assert(serializer);
                if (!serializer) throw std::runtime_error("Serializer == nullptr!");
                serializer->Serialize(snapshot, autoSaveFileName);
                isSaving.store(false);
            }
            catch (const std::exception& e) 
            {
                std::cerr << e.what() << '\n';
                isSaving.store(false);
            }
        });
    }

    bool IsSaving() const noexcept override { return isSaving.load(); }

    void SetSaveCounter(uint8_t newSaveCounter) override { saveCounter.store(newSaveCounter); }

    uint8_t GetSaveCounter() const noexcept override { return saveCounter.load(); }

	std::string GetSerializationLog() const noexcept override { return serializer->GetSerializationLog(); }

    ~AutoSaveManager() override { if (saveFuture.valid()) { saveFuture.wait(); } }
};
