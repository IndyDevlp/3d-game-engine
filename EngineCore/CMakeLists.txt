cmake_minimum_required(VERSION 3.12)

set(CORE 3d-game-engine-core)

add_library(${CORE} STATIC 
	src/Core/Utilts/test.cpp
	include/Core/Utilts/test.hpp
)

target_include_directories(${CORE} PUBLIC include)
target_compile_features(${CORE} PUBLIC cxx_std_17)