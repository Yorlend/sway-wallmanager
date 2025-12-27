#pragma once

#include <filesystem>

class DaemonManager
{
public:
	static constexpr const char* c_pidfile = "wallmanagerd.pid";

public:
	static void Daemonize();
	static pid_t GetPid();

private:
	DaemonManager();
	DaemonManager(DaemonManager&&) = delete;

	static DaemonManager& Instance();
	pid_t Daemonize_();
	void SetupLogging();
	void ExitIfAlreadyRunning();
	void SetupExitCallback();

private:
	std::filesystem::path m_pidfile;
	pid_t m_pid{-1};
};

