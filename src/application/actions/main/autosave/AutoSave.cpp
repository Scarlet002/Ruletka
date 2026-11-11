#include "AutoSave.h"
#include "ApplicationState.h"
#include "AutoSaveManager.h"
#include "DecisionState.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "Logger.h"
#include <boost/static_string/static_string.hpp>
#include <format>
#include <iterator>
#include <optional>

AutoSave::~AutoSave() noexcept = default;

AutoSave::AutoSave(ApplicationState& app, DomainState& domain, Logger& logger, AutoSaveManager& async) noexcept
    : m_app(app), m_domain(domain), m_logger(logger), m_async(async)
{
}

auto AutoSave::Execute() -> void
{
    m_app.GetDecisionState().SetMainChoice(std::nullopt);
    if (!m_async.IsSaving())
    {
        m_async.SaveSnapshotAsync(m_app, m_domain);
        boost::static_string<GameConfig::LOG_LINE_RESERVE> log;
        std::format_to(std::back_inserter(log), "Save completed: autosave{}", m_async.GetSaveCounter());
        m_logger.UpdateLogs(log);
    }
}
