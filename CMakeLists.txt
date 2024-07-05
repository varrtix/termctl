cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(termctl LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

# include(FetchContent)
# FetchContent_Declare(
#   readline
#   URL https://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz
#   URL_HASH SHA256=79c57f7b0b3d541e659d50cc0011a4d7d96ad2339d9f82f8af16e4c1e11c384e
# )
#
# FetchContent_MakeAvailable(readline)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Readline REQUIRED readline)

file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cc)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${Readline_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} ${Readline_LIBRARIES})
