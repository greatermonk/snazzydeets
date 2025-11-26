cmake_minimum_required(VERSION 3.10)
project(SnazzyDeets VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20) # Using modern C++

include_directories(console_colors)
set(MODULES
    graphs
    trees
    maps
    linked_lists
)

foreach(mod ${MODULES})
       file(GLOB SRC_FILES "${mod}/*.cpp")

       if (SRC_FILES)
          add_executable(${mod}_run ${SRC_FILES})
          target_include_directories(${mod}_run PRIVATE ${mod})
       endif()
endforeach()

foreach(mod ${MODULES})
       install(TARGETS ${mod}_run DESTINATION bin)
endforeach()
