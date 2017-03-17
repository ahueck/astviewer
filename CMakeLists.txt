CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(astviewer)

include(${PROJECT_SOURCE_DIR}/cmake/ToolchainOptions.cmake)

set(CMAKE_VERBOSE_MAKEFILE true)

if(NOT BINARY_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
endif()


#set(ast_dump_src)
#add_library(ast_dump ${ast_dump_src})
#include_directories(ast_dump 
#  PUBLIC 
#  ${PROJECT_SOURCE_DIR}/include
#)

add_executable(${PROJECT_NAME}${EXE_SUFFIX} src/main.cpp)
#target_link_libraries(${PROJECT_NAME}${EXE_SUFFIX} ast_dump)
include_directories(${PROJECT_NAME}${EXE_SUFFIX}
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)

enable_testing()
add_subdirectory(test)

