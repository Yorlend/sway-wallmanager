set(UNIT_NAME wallmanagerd)
set(CMAKE_CXX_STANDARD 20)

add_executable(${UNIT_NAME})

target_sources(${UNIT_NAME} PRIVATE
	main.cc
	managers/DaemonManager.cc
	managers/ConfigManager.cc
)
target_include_directories(${UNIT_NAME} PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
)

