#pragma once

#include <filesystem>
#include <vector>
#include <string>

namespace swm
{

struct DirectoryState
{
	DirectoryState() = default;
	explicit DirectoryState(std::vector<std::string> entries, std::filesystem::path cwd = std::filesystem::current_path())
		: entries(entries)
		, cwd(cwd)
	{
	}

	std::vector<std::string> entries;
	std::filesystem::path cwd;
	int selected{};

	void Refresh(std::vector<std::string> const& new_entries)
	{
		entries = new_entries;
		selected = 0;
	}

	std::string GetSelectedEntry()
	{
		return entries.at(selected);
	}
};

}
