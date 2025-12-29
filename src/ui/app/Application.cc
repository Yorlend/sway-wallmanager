#include "Application.h"
#include "components/App.h"

#include <ftxui/component/screen_interactive.hpp>

#include <cstdlib>

swm::Application::Application() = default;

void swm::Application::Run()
{
	using namespace ftxui;

	auto screen = ScreenInteractive::TerminalOutput();

	auto root_component = components::App()
	                    | CatchEvent([&](Event e) {
			if (e == Event::Character('q')) {
				screen.ExitLoopClosure()();
				return true;
			}
			return false;
		});

	screen.Loop(root_component);
}

