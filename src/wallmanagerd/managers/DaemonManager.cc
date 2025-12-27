#include "DaemonManager.h"

#include <unistd.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/types.h>
#include <cstdlib>
#include <filesystem>
#include <cstdio>
#include <fcntl.h>
#include <syslog.h>
#include <csignal>

DaemonManager::DaemonManager()
{
	std::filesystem::path xdg_runtime_dir{ std::getenv("XDG_RUNTIME_DIR") };
	m_pidfile = xdg_runtime_dir / c_pidfile;
}

void DaemonManager::Daemonize()
{
	auto& mngr = Instance();
	if (mngr.m_pid < 0) {
		mngr.m_pid = mngr.Daemonize_();
		mngr.SetupLogging();
		mngr.ExitIfAlreadyRunning();
		mngr.SetupExitCallback();
	}
}

pid_t DaemonManager::GetPid()
{
	return Instance().m_pid;
}

void DaemonManager::SetupLogging()
{
	openlog("wallmanagerd", LOG_PID, LOG_DAEMON);
}

void DaemonManager::ExitIfAlreadyRunning()
{
	auto fd = open(Instance().m_pidfile.c_str(), O_RDWR | O_CREAT, 0644);
	if (fd < 0) {
		syslog(LOG_INFO, "daemon is already running");
		std::exit(-1);
	}

	if (flock(fd, LOCK_EX | LOCK_NB) < 0) {
		syslog(LOG_INFO, "daemon is already running");
		close(fd);
		std::exit(-1);
	}

	if (ftruncate(fd, 0) < 0 ||
	    dprintf(fd, "%ld\n", static_cast<long>(getpid())) < 0 ||
	    fsync(fd) < 0)
	{
		syslog(LOG_INFO, "daemon is already running");
		close(fd);
		std::exit(-1);
	}

	syslog(LOG_INFO, "wallmanagerd daemon started");
}

void DaemonManager::SetupExitCallback()
{
	static bool once = []{
		std::atexit([]{
			syslog(LOG_INFO, "DELETING PIDFILE");
			std::filesystem::remove(Instance().m_pidfile);
		});
		std::signal(SIGTERM, [](int){ std::exit(0); });
		std::signal(SIGINT,  [](int){ std::exit(0); });
		return true;
	}();
}

DaemonManager& DaemonManager::Instance()
{
	static DaemonManager mngr;
	return mngr;
}

pid_t DaemonManager::Daemonize_()
{
	auto pid = fork();
	if (pid < 0)
		return -1;
	if (pid > 0)
		std::exit(0);

	if (setsid() < 0)
		return -1;

	pid = fork();
	if (pid < 0)
		return -1;
	if (pid > 0)
		std::exit(0);

	umask(0);
	chdir("/");

	for (auto fd = sysconf(_SC_OPEN_MAX); fd >= 0; --fd)
		close(fd);

	int nullfd = open("/dev/null", O_RDWR);
	dup2(nullfd, STDIN_FILENO);
	dup2(nullfd, STDOUT_FILENO);
	dup2(nullfd, STDERR_FILENO);
	if (nullfd > 2)
		close(nullfd);

	return getpid();
}

