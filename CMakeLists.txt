cmake_minimum_required(VERSION 2.8.4)
project(regeringskris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp GameEngine.cpp world/entity.cpp world/env.cpp util.cpp)
add_executable(regeringskris ${SOURCE_FILES})

#file(COPY intro.txt DESTINATION ${CMAKE_BINARY_DIR} )

configure_file(intro.txt intro.txt COPYONLY)