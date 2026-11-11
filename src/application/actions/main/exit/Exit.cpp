#include "Exit.h"
#include "GameEnums.h"
#include "GameLoopState.h"

Exit::~Exit() noexcept = default;

Exit::Exit(GameLoopState& gameLoopState) noexcept : m_gameLoopState(gameLoopState)
{
}

auto Exit::Execute() -> void
{
    m_gameLoopState.SetStateOfGameLoop(GameEnums::YesNo::NO);
}
