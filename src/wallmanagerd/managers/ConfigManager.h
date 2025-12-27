#pragma once

#include <filesystem>
#include <optional>

/*
 * Config is primitive for now
 * a single filepath for wallpaper
 * on every screen
 */
class ConfigManager
{
public:
	ConfigManager();
	bool Changed();
	std::optional<std::filesystem::path> GetWallpaperPath() const;

private:
	std::filesystem::path m_config_path;
	std::filesystem::file_time_type m_last_mod{};
};

