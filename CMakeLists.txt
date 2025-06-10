cmake_minimum_required(VERSION 3.10)

# check platform compatibility
if(NOT CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    message(FATAL_ERROR "This project is only supported on Linux.")
endif()


# define project
project(tprocess VERSION 0.0.1 LANGUAGES C)

# set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# source files
set(SOURCES
    src/main.c
    src/tp_core.c
    src/tp_logger.c
)

# create executable
add_executable(tprocess ${SOURCES})

# include directories
target_include_directories(tprocess PRIVATE include)
