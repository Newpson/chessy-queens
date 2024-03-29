add_library(Queens STATIC)
target_sources(Queens
	PRIVATE queens.c
	PUBLIC queens.h)
# target_compile_options(Queens
# 	PRIVATE -DNDEBUG)
target_include_directories(Queens
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(Queens
	PUBLIC Log)
