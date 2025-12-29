#include "ApplicationManager.h"

#include <cstdlib>

swm::ApplicationManager::ApplicationManager() = default;

auto swm::ApplicationManager::Instance() -> ApplicationManager&
{
	static ApplicationManager mngr;
	return mngr;
}

auto swm::ApplicationManager::GetConfigService() -> ConfigService&
{
	return Instance().m_cfg_service;
}

auto swm::ApplicationManager::GetFileService() -> FileService&
{
	return Instance().m_file_service;
}

