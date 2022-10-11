cmake_minimum_required(VERSION 3.12)

set(CORE 3d-game-engine-core)

set(CORE_PUBLIC_INCLUDES
 include/Core/Application.hpp
 include/Core/Log.hpp
)

set(CORE_PRIVATE_SOURCES
 src/Core/Application.cpp
)

add_library(${CORE} STATIC 
	${CORE_PUBLIC_INCLUDES}
	${CORE_PRIVATE_SOURCES}
)

target_include_directories(${CORE} PUBLIC include)
target_compile_features(${CORE} PUBLIC cxx_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${CORE} PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${CORE} PRIVATE spdlog)