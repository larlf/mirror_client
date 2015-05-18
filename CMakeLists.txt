project(test)

#版本检查
cmake_minimum_required(VERSION 2.6)

#设置Debug版的编译参数，Windows下只支持Debug版
set(CMAKE_CXX_FLAGS				"-DWIN32 /MT /EHsc -D_WIN32_WINNT=0x0501 -DWINDOWS")
set(CMAKE_CXX_FLAGS_DEBUG		"/MTd -DDEBUG /Z7")

#设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(test_src
	src/main.cpp
	src/test1.h
	src/test1.cpp
)
link_directories(${PROJECT_SOURCE_DIR}/deps/win32/debug/lib ${PROJECT_BINARY_DIR}/../bin)
include_directories(${PROJECT_SOURCE_DIR}/deps/win32/debug/include)
add_executable(3dtest ${test_src})
target_link_libraries(3dtest
	winmm.lib
	opengl32.lib
	glu32.lib
	gtestd.lib
	glfw3.lib
)

