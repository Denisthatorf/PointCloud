cmake_minimum_required(VERSION 3.5)

project(cutSphereMove LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER "clang")

file(GLOB SOURCES_C "src/*.c" "src/*/*.c" "src/*/*/*.c" "src/*/*/*/*.c")
file(GLOB SOURCES_CPP "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp")

add_executable(cutSphereMove ${SOURCES_C} ${SOURCES_CPP})

target_include_directories (cutSphereMove
			PUBLIC 
				${CMAKE_SOURCE_DIR}/src/
				${CMAKE_SOURCE_DIR}/src/core/
				${CMAKE_SOURCE_DIR}/src/helpers/
)
