#pragma once

#include <filesystem>

namespace swm
{

// TODO: Merge ConfigManager and ConfigService -> to common
class ConfigService
{
public:
	ConfigService();
	bool ChangeWallpaper(std::filesystem::path const& wallpaper);

private:
	std::filesystem::path m_cfg_path;
};

}

