#include "managers/DaemonManager.h"

#include <unistd.h>
#include <syslog.h>

int main()
{
	// TODO: add kill command

	DaemonManager::Daemonize();

	for (;;)
	{
		sleep(5);
		syslog(LOG_INFO, "5 seconds passed");
	}
}
