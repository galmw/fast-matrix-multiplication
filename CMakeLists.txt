cmake_minimum_required (VERSION 2.8.12)

# Change project name
set (PROJECT_NAME fast-matrix-multiplication)
set (PROJECT_TEST_NAME ${PROJECT_NAME}-ut)

project (${PROJECT_NAME} C CXX)

# Folder where the Coverage module is
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# Source files folder
set (SRC_DIR src)

# Header files folder
set (INCL_DIR include)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

include_directories (${PROJECT_SOURCE_DIR}/${INCL_DIR})

# Important: Include all source files on this list
set (SOURCE
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/matmul_standard.cpp
    ${SRC_DIR}/matmul_strassen.cpp
    ${SRC_DIR}/matmul_ks.cpp
    ${SRC_DIR}/matrix.cpp
)

# Output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# Add framework
find_library(ACCELERATE_FRAMEWORK Accelerate)

# Add the executable for the program
add_executable (${PROJECT_NAME} ${SOURCE})

# Linj the framework
target_link_libraries(${PROJECT_NAME} ${ACCELERATE_FRAMEWORK})