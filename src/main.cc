#include <ftxui/component/component.hpp>

int main()
{
	using namespace ftxui;

	Element doc = hbox({
		text("left") | border,
		text("middle") | border | flex,
		text("right") | border,
	});

	auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
	Render(screen, doc);
	screen.Print();
}

