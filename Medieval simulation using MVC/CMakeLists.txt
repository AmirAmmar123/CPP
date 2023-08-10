cmake_minimum_required(VERSION 3.25)
project(homework3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

# SimObject
set(SimH SimObject/SimObject.h SimObject/Structure/Structure.h SimObject/Structure/Castle/Castle.h SimObject/Structure/Farm/Farm.h SimObject/Agent/Agent.h SimObject/Agent/Peasent/Peasant.h SimObject/Agent/Knight/Knight.h SimObject/Agent/Thug/Thug.h)
set(SimS SimObject/Agent/Knight/Knight.cpp SimObject/Agent/Peasent/Pesant.cpp SimObject/Agent/Thug/Thug.cpp SimObject/Structure/Farm/Farm.cpp SimObject/Structure/Castle/Castle.cpp)

# Abstract agent_factory and structer_factory
set(ABSFACTORY Factory/agent_factory/factory.h)

# Moving Object
set(MovingH SimObject/MovingObject.h SimObject/MovingObject.cpp)

#Model
set(Model_H_S Model/Model.h Model/Model.cpp)

# Viewer
set(ViewerH Viewer/Viewer.h Viewer/Viewer.cpp)

# Controller
set(ControllerH Controller/Controller.h SimObject/MovingObject.h SimObject/Agent/Agent.cpp SimObject/SimObject.cpp Controller/Controller.cpp)

# Utilities
set(Utilities  Utilities/Validator.h "Utilities/Geometry.cpp"  "Utilities/Geometry.h" Utilities/Tookenizer.h Utilities/Validator.cpp)
#Executable
add_executable(homework3 ${Utilities} ${ClassID_H} ${ABSFACTORY} ${MovingH} ${MATH} ${ViewerH}  ${Model_H_S} ${ControllerH} ${SimH} ${SimS}  main.cpp)
