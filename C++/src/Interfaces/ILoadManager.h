#pragma once
#include "ForwardDeclarations.h"
#include <string>

class ILoadManager
{
public:
    virtual void LoadGameState(GameState& state, 
        const std::string& fileName) = 0;

    virtual ~ILoadManager() = default;
};
