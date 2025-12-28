#include "managers/DaemonManager.h"
#include "managers/ConfigManager.h"
#include "sway/wallpaper.h"

#include <unistd.h>
#include <syslog.h>
#include <cstdlib>

int main()
{
	// TODO: add kill command

	DaemonManager::Daemonize();

	ConfigManager config;
	for (;;)
	{
		if (config.Changed())
			if (auto wall = config.GetWallpaperPath())
				sway::SetWallpaper(wall->c_str());
		sleep(5);
	}
}

