#pragma once


#include "services/FileService.h"
#include "services/ConfigService.h"

namespace swm
{

class ApplicationManager
{
public:
	static ConfigService& GetConfigService();
	static FileService& GetFileService();

private:
	ApplicationManager();
	ApplicationManager(ApplicationManager&&) = delete;
	static ApplicationManager& Instance();

private:
	ConfigService m_cfg_service{};
	FileService   m_file_service{};
};

}

