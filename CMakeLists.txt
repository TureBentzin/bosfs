cmake_minimum_required(VERSION 3.30)
project(bosfs)

set(CMAKE_CXX_STANDARD 20)


# compile bosfs-lib as a dynamic library
add_subdirectory(bosfs-lib)

# compile bosfs as an executable

# glob source files
file(GLOB_RECURSE BOSFS_SOURCES *.cpp *.c)

add_executable(bosfs ${BOSFS_SOURCES})

target_link_libraries(bosfs bosfs-lib)


