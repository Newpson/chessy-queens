add_library(Log INTERFACE)
target_sources(Log
	PUBLIC log.h)
target_include_directories(Log
	INTERFACE ${CMAKE_CURRENT_LIST_DIR})
