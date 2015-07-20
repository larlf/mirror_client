project(MagicMirror)

# 版本检查
cmake_minimum_required(VERSION 2.6)

# 设置Debug版的编译参数，Windows下只支持Debug版
set(CMAKE_CXX_FLAGS				"-DWIN32 /MD /EHsc /wd\"4819\"")
set(CMAKE_CXX_FLAGS_DEBUG		"/MDd -DDEBUG /ZI /Od")

# 设置Link参数
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")

# 设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Mirror Core
set(core_src
	src/core/mm_const.h
	src/core/mm_const.cc
	src/core/mm_utils.h
	src/core/mm_utils.cc
	src/core/mm_app.h
	src/core/mm_app.cc
	src/core/mm_game.h
	src/core/mm_game.cc
	src/core/mm_opengl.h
	src/core/mm_opengl.cc
)
link_directories(${PROJECT_SOURCE_DIR}/lib ${PROJECT_BINARY_DIR}/bin)
include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/deps/win32/debug/include)
add_library(mm_core STATIC ${core_src})	

# 测试项目
set(test_src
	src/test/main.cpp
	src/test/opengl_test.h
	src/test/opengl_test.cpp
)
link_directories(${PROJECT_SOURCE_DIR}/deps/win32/debug/lib ${PROJECT_BINARY_DIR}/../bin)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/deps/win32/debug/include)
add_executable(mm_test ${test_src})
target_link_libraries(mm_test
	winmm.lib
	gtest.lib
	opengl32.lib
	glu32.lib
	glew32d.lib
    freeglutd.lib
    iconv.lib
    mm_core.lib
)

