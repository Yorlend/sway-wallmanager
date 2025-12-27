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

void DaemonManager::Daemonize()
{
	std::lock_guard _(m_mutex);
	auto& mngr = Instance();
	if (mngr.m_pid < 0)
		mngr.m_pid = mngr.Daemonize_();
}

pid_t DaemonManager::GetPid()
{
	std::lock_guard _(m_mutex);
	return Instance().m_pid;
}

bool DaemonManager::IsRunning()
{
	std::filesystem::path pidfile_path;
	if (const char* rt = std::getenv("XDG_RUNTIME_DIR"))
		pidfile_path = std::filesystem::path(rt) / c_pidfile;

	auto fd = open(pidfile_path.c_str(), O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		return true;

	if (flock(fd, LOCK_EX | LOCK_NB) < 0) {
		close(fd);
		return true;
	}

	if (ftruncate(fd, 0) < 0 ||
	    dprintf(fd, "%ld\n", static_cast<long>(getpid())) < 0 ||
	    fsync(fd) < 0)
	{
		close(fd);
		return true;
	}

	return false;
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
		_exit(0);

	if (setsid() < 0)
		return -1;

	pid = fork();
	if (pid < 0)
		return -1;
	if (pid > 0)
		_exit(0);

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

