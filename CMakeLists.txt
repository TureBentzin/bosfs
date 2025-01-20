cmake_minimum_required(VERSION 3.30)
project(bosfs)

set(CMAKE_CXX_STANDARD 20)

# Compile bosfs-lib as a dynamic library
add_subdirectory(bosfs-lib)

file(GLOB BOSFS_SOURCES # only in the current directory
        cli/*.cpp
        cli/*.c
)

message("Detected source files: ${BOSFS_SOURCES}")

add_executable(bosfs ${BOSFS_SOURCES})

# Link bosfs-lib
target_link_libraries(bosfs PRIVATE bosfs-lib)

# Include directories for the bosfs executable
target_include_directories(bosfs PRIVATE bosfs-lib/include)


add_custom_command(
        TARGET bosfs POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:bosfs-lib> $<TARGET_FILE_DIR:bosfs>
        COMMENT "Copying bosfs-lib.dll to the output directory"
)