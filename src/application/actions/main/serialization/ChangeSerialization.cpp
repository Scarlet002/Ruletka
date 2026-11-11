#include "ChangeSerialization.h"
#include "ApplicationState.h"
#include "DecisionState.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Logger.h"
#include "SerializationManager.h"
#include "SerializationState.h"
#include <optional>

ChangeSerialization::~ChangeSerialization() noexcept = default;

ChangeSerialization::ChangeSerialization(ApplicationState& app, Logger& logger,
                                         SerializationManager& serialization) noexcept
    : m_app(app), m_logger(logger), m_serialization(serialization)
{
}

auto ChangeSerialization::Execute() -> void
{
    auto& loop = m_app.GetGameLoopState();
    loop.SetCurrentMenu(GameEnums::Window::SERIALIZATION_MENU);
    auto& decision = m_app.GetDecisionState();
    const auto action = decision.GetSerializationChoice();
    if (!action.has_value())
    {
        return;
    }

    const auto sType = action.value();
    m_app.GetSerializationState().SetSerializationType(sType);
    m_serialization.SetSerializationMethod(sType);

    if (sType == GameEnums::SerializationFormat::JSON)
    {
        m_logger.UpdateLogs("Serialization format: JSON!");
    }
    else
    {
        m_logger.UpdateLogs("Serialization format: TXT!");
    }

    decision.SetSerializationChoice(std::nullopt);
    decision.SetMainChoice(std::nullopt);
    loop.SetCurrentMenu(GameEnums::Window::MAIN_MENU);
}
