#pragma once

#include "GameEnums.h"
#include "UI.h"
#include <memory>
#include <unordered_map>

class UIManager final
{
private:
    std::unordered_map<GameEnums::UIType, std::unique_ptr<UI>> m_uis;
    UI* m_currentUI = nullptr;

public:
    auto SetUIType(GameEnums::UIType uiKey) -> void;
    auto AddUIType(GameEnums::UIType uiKey, std::unique_ptr<UI> uiVersion) -> void;
    auto GetInput() -> void;
    auto Initialize() -> void;
    auto Render() const -> void;
};
