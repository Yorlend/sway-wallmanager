set(UNIT_NAME sway-wallmanager)
include(${CMAKE_SOURCE_DIR}/cmake/deps.cmake)

set(CMAKE_CXX_STANDARD 20)
add_executable(${UNIT_NAME})

target_sources(${UNIT_NAME} PRIVATE
	app/Application.cc
	app/ApplicationManager.cc
	components/App.cc
	services/ConfigService.cc
	services/FileService.cc
	main.cc
)
target_include_directories(${UNIT_NAME} PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		ftxui::screen
		ftxui::dom
		ftxui::component
)


