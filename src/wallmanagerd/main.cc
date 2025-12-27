#include "managers/DaemonManager.h"
#include "managers/ConfigManager.h"

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
		sleep(5);
		if (config.Changed())
			if (auto wall = config.GetWallpaperPath())
				syslog(LOG_INFO, "new wallpaper %s", wall->c_str());
	}
}

