cmake_minimum_required(VERSION 3.30)
project(bosfs-lib)

set(CMAKE_CXX_STANDARD 20)


# compile bosfs-lib as a dynamic library
# headers in bosfs-lib/include/
# sources in bosfs-lib/

# glob source files

file(GLOB_RECURSE BOSFS_LIB_SOURCES *.cpp *.c)

# glob header files
file(GLOB_RECURSE BOSFS_LIB_HEADERS include/*.h include/*.hpp)

# add bosfs-lib as a shared library
add_library(bosfs-lib SHARED ${BOSFS_LIB_SOURCES} ${BOSFS_LIB_HEADERS})


set_target_properties(bosfs-lib PROPERTIES VERSION 1.0)

target_include_directories(bosfs-lib PRIVATE .)