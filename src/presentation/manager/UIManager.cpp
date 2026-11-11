#include "UIManager.h"
#include "GameEnums.h"
#include "UI.h"
#include <memory>
#include <stdexcept>
#include <utility>

auto UIManager::SetUIType(GameEnums::UIType uiKey) -> void
{
    const auto iterator = m_uis.find(uiKey);
    if (iterator == m_uis.end())
    {
        throw std::runtime_error("UI is nullptr!");
    }
    m_currentUI = iterator->second.get();
}

auto UIManager::AddUIType(GameEnums::UIType uiKey, std::unique_ptr<UI> uiVersion) -> void
{
    const auto [iterator, inserted] = m_uis.emplace(uiKey, std::move(uiVersion));
    if (!inserted)
    {
        throw std::runtime_error("Trying to duplicate UI!");
    }
    if (m_currentUI == nullptr)
    {
        m_currentUI = iterator->second.get();
    }
}

auto UIManager::GetInput() -> void
{
    if (m_currentUI == nullptr)
    {
        throw std::runtime_error("UI is nullptr!");
    }
    m_currentUI->GetInput();
}

auto UIManager::Initialize() -> void
{
    if (m_currentUI == nullptr)
    {
        throw std::runtime_error("Ui is nullptr!");
    }
    m_currentUI->Initialize();
}

auto UIManager::Render() const -> void
{
    if (m_currentUI == nullptr)
    {
        throw std::runtime_error("Ui is nullptr!");
    }
    m_currentUI->Render();
}
