#include "ConfigService.h"

#include <cstdlib>
#include <array>
#include <algorithm>
#include <fstream>

namespace swm
{

constexpr std::array<std::string_view, 6> c_image_formats = {
	".png",
	".jpg",
	".jpeg",
	".tiff",
	".tif",
	".gif"
};

}

swm::ConfigService::ConfigService()
{
	char const* home = std::getenv("HOME");
	if (!home)
		throw std::runtime_error("HOME environment variable is not set");
	m_cfg_path = std::filesystem::path(home) / ".config" / "wallmanagerd" / "config";
}

bool swm::ConfigService::ChangeWallpaper(std::filesystem::path const& wallpaper)
{
	if (wallpaper.has_extension() &&
	    std::ranges::find(c_image_formats, wallpaper.extension().string()) != c_image_formats.end())
	{
		std::ofstream cfg(m_cfg_path);
		cfg << wallpaper.string();
		return true;
	}
	return false;
}

