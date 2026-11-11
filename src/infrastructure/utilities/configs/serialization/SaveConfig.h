#pragma once

#include <string_view>

class SaveConfig final
{
public:
    SaveConfig() = delete;

    [[nodiscard]]
    static constexpr auto GetSaveDirectory() -> std::string_view
    {
        return "data/saves";
    }

    [[nodiscard]]
    static constexpr auto GetAutoSaveDirectory() -> std::string_view
    {
        return "data/saves/autosaves";
    }

    [[nodiscard]]
    static auto CreateDirectoryIfNotExists(std::string_view path) -> bool;
};
