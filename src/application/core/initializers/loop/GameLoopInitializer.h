#pragma once

#include "Initializer.h"

class ApplicationState;
class DomainState;

class GameLoopInitializer final : public Initializer
{
private:
    ApplicationState& m_appState;
    DomainState& m_domainState;

public:
    GameLoopInitializer(ApplicationState& appState, DomainState& domainState) noexcept;

    auto Initialize() -> void override;
};
