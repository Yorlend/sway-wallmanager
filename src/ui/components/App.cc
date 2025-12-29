#include "App.h"

#include "app/ApplicationManager.h"
#include "states/DirectoryState.h"

#include <ftxui/component/event.hpp>

namespace
{

class AppImpl : public ftxui::ComponentBase
{
public:
	AppImpl()
		: m_state(swm::ApplicationManager::GetFileService().Pwd())
	{
		using namespace ftxui;
		m_menu = Menu(&m_state.entries, &m_state.selected);

		m_container = Container::Vertical({m_menu})
		            | CatchEvent([this](Event e) { return HandleEvent(e); }); 

		Add(Renderer(m_container, [&, this] {
			return vbox({
				hbox(text("selected = "), text(m_state.GetSelectedEntry())),
				separator(),
				m_menu->Render() | frame | size(HEIGHT, LESS_THAN, 10),
			}) | border;
		}));
	}

private:
	swm::DirectoryState m_state;
	ftxui::Component    m_container;
	ftxui::Component    m_menu;

	bool HandleEvent(ftxui::Event e)
	{
		using namespace ftxui;

		auto& file_svc = swm::ApplicationManager::GetFileService();
		if (e == Event::Return) {
			
			if (auto target_file = file_svc.GetCwd() / m_state.GetSelectedEntry();
			    std::filesystem::is_directory(target_file))
			{
				file_svc.ChangeDir(m_state.GetSelectedEntry());
				m_state.Refresh(file_svc.Pwd());
				return true;
			}
			else
			{
				swm::ApplicationManager::GetConfigService().ChangeWallpaper(file_svc.GetCwd() / target_file);
				return true;
			}
		}
		else if (e == Event::Backspace) {
			file_svc.Back();
			m_state.Refresh(file_svc.Pwd());
			return true;
		}
		return false;
	}
};

}

ftxui::Component swm::components::App()
{
	return std::make_shared<AppImpl>();
}

