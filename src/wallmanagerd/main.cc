#include "managers/DaemonManager.h"

#include <unistd.h>
#include <syslog.h>

int main()
{

	DaemonManager::Daemonize();
	if (DaemonManager::IsRunning()) {
		syslog(LOG_INFO, "Daemon is already running");
		return -1;
	}

	openlog("wallmanagerd", LOG_PID, LOG_DAEMON);
	syslog(LOG_INFO, "wallmanagerd daemon started");

	for (;;)
	{
		sleep(5);
		syslog(LOG_INFO, "5 seconds passed");
	}
}
