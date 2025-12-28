#pragma once

#include <cstdlib>
#include <unistd.h>

namespace sway
{

inline void SetWallpaper(char const* path, char const* mode = "fill")
{
	::system("pkill -x swaybg");
	if (fork() == 0) {
		execlp("swaybg", "swaybg", "-i", path, "-m", mode, nullptr);
		std::exit(1); // exec failed
	}
}

}

