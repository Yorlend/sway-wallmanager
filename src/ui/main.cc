#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include <span>
#include <filesystem>
#include <array>
#include <fstream>

using namespace std::chrono_literals;

constexpr std::array<std::string_view, 6> image_formats = {
	".png",
	".jpg",
	".jpeg",
	".tiff",
	".tif",
	".gif"
};

std::vector<std::string> ListPwd(std::filesystem::path const& path)
{
	std::vector<std::string> res;
	for (auto const& entry : std::filesystem::directory_iterator(path))
		res.push_back(entry.path().filename().string());
	return res;
}

ftxui::Components Directories(std::span<std::string> dirs)
{
	ftxui::Components components;
	for (auto dir : dirs)
		components.push_back( ftxui::MenuEntry(dir) );
	return components;
}

int main()
{
	using namespace ftxui;
	auto screen = ScreenInteractive::TerminalOutput();

	int selected{};
	auto pwd = std::filesystem::current_path();
	auto dir_entries = ListPwd(pwd);

	auto menu = Menu(&dir_entries, &selected);
	auto container = Container::Vertical({ menu });


	container |= CatchEvent([&](Event e) {
		if (e == Event::Character('q')) {
			screen.ExitLoopClosure()();
			return true;
		}
		else if (e == Event::Return) {
			auto target_file = pwd / dir_entries[selected];
			if (std::filesystem::is_directory(target_file)) {
				pwd /= dir_entries[selected];
				dir_entries = ListPwd(pwd);
				selected = 0;
				return true;
			}
			else if (target_file.has_extension() &&
			         std::ranges::find(image_formats, target_file.extension().string()) != image_formats.end())
			{
				std::ofstream config_file(std::filesystem::path(std::getenv("HOME")) / ".config" / "wallmanagerd" / "config");
				config_file << target_file.c_str();

				return true;
			}
		}
		else if (e == Event::Backspace) {
			pwd /= "..";
			dir_entries = ListPwd(pwd);
			selected = 0;
			return true;
		}
		return false;
	});


	auto renderer = Renderer(container, [&] {
	return vbox({
				hbox(text("selected = "), text(dir_entries[selected])),
				separator(),
				menu->Render() | frame | size(HEIGHT, LESS_THAN, 10),
			}) |
			border;
	});
	screen.Loop(renderer);
}

