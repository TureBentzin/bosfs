cmake_minimum_required(VERSION 3.30)
project(bosfs-lib)

set(CMAKE_CXX_STANDARD 20)


# compile bosfs-lib as a dynamic library
# headers in bosfs-lib/include/
# sources in bosfs-lib/

# glob source files

file(GLOB_RECURSE BOSFS_LIB_SOURCES *.cpp *.c)
message("Detected source files: ${BOSFS_LIB_SOURCES}")

# add bosfs-lib as a shared library
add_library(bosfs-lib SHARED ${BOSFS_LIB_SOURCES})


set_target_properties(bosfs-lib PROPERTIES VERSION 1.0)

target_include_directories(bosfs-lib PRIVATE ./include)

# Define the BOSFS_LIB_EXPORTS macro for shared library builds
target_compile_definitions(bosfs-lib PRIVATE BOSFS_LIB_EXPORTS)

