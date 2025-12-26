cmake_minimum_required(VERSION 3.28)
project(sway-wallmanager)

include(cmake/deps.cmake)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	src/main.cc
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		ftxui::screen
		ftxui::dom
		ftxui::component
)

