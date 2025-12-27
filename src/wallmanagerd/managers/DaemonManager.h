#pragma once

#include <mutex>

class DaemonManager
{
public:
	static constexpr const char* c_pidfile = "wallmanagerd.pid";

public:
	static void Daemonize();
	static pid_t GetPid();
	static bool IsRunning();

private:
	DaemonManager() = default;
	DaemonManager(DaemonManager&&) = delete;

	static DaemonManager& Instance();
	pid_t Daemonize_();

private:
	pid_t m_pid{-1};
	static inline std::mutex m_mutex;
};

