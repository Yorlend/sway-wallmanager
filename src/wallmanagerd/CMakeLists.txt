set(UNIT_NAME wallmanagerd)

add_executable(${UNIT_NAME})

target_sources(${UNIT_NAME} PRIVATE
	main.cc
	managers/DaemonManager.cc
)
target_include_directories(${UNIT_NAME} PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
)

