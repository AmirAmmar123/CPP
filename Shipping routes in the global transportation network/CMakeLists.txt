cmake_minimum_required(VERSION 3.25)
project(49_ex2_205744873)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(CMAKE_CXX_STANDARD 14)
set(GRAPH Graph.h GraphLoader.h Factory.h Factory.cpp GraphLoader.cpp Graph.cpp)
set(LIB Validator.h Chrono.h Chrono.cpp Validator.cpp  Triple.h)
set(VER_EDG Vertex.h Edge.h Vertex_impl.h)
set(COMMANDLINE CommandLine.h CommandLine.cpp CommandMapper.h)

add_executable(49_ex2_205744873 ${LIB} ${GRAPH} ${VER_EDG} ${COMMANDLINE} main.cpp)
