#pragma once

#include <filesystem>
#include <vector>
#include <string>

namespace swm
{

class FileService
{
public:
	explicit FileService(std::filesystem::path cwd = std::filesystem::current_path());
	std::vector<std::string> Pwd() const;
	void ChangeDir(std::string directory);
	void Back();
	std::filesystem::path const& GetCwd() const;

private:
	std::filesystem::path m_cwd;
};

}

