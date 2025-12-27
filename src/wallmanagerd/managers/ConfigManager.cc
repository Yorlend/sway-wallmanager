#include "ConfigManager.h"

#include <syslog.h>
#include <fstream>

ConfigManager::ConfigManager()
{
	const char* home = std::getenv("HOME");
	const char* xdgconfig = std::getenv("XDG_CONFIG_HOME");

	std::filesystem::path config_dir = xdgconfig
	                                 ? std::filesystem::path{xdgconfig} / "wallmanagerd"
	                                 : std::filesystem::path{home} / ".config" / "wallmanagerd";

	if (!std::filesystem::exists(config_dir))
		std::filesystem::create_directories(config_dir);

	m_config_path = config_dir / "config";
	if (!std::filesystem::exists(m_config_path))
		std::ofstream conf(m_config_path);
}

bool ConfigManager::Changed()
{
	if (std::filesystem::exists(m_config_path)) {
		if (auto mod_time = std::filesystem::last_write_time(m_config_path);
		    m_last_mod == std::filesystem::file_time_type{} ||
		    mod_time > m_last_mod)
		{
			m_last_mod = mod_time;
			return true;
		}
	}
	return false;
}

std::optional<std::filesystem::path> ConfigManager::GetWallpaperPath() const
{
	std::ifstream config(m_config_path);
	if (config.is_open()) {
		if (std::string wallpaper; std::getline(config, wallpaper)) {
			return std::filesystem::exists(wallpaper) ? std::make_optional<std::filesystem::path>(wallpaper) : std::nullopt;
		}
	}
	return std::nullopt;
}

