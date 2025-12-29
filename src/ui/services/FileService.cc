#include "FileService.h"

swm::FileService::FileService(std::filesystem::path cwd)
	: m_cwd(std::move(cwd))
{
}

std::vector<std::string> swm::FileService::Pwd() const
{
	std::vector<std::string> res;

	for (auto const& entry : std::filesystem::directory_iterator(m_cwd))
		res.push_back(entry.path().filename().string());

	return res;
}

void swm::FileService::ChangeDir(std::string directory)
{
	if (std::filesystem::is_directory(m_cwd / directory) && !std::filesystem::is_empty(m_cwd / directory))
		m_cwd /= directory;
}

void swm::FileService::Back()
{
	m_cwd = m_cwd.parent_path();
}

std::filesystem::path const& swm::FileService::GetCwd() const
{
	return m_cwd;
}

