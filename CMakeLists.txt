cmake_minimum_required(VERSION 3.3)
project(DIRT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_VERBOSE_MAKEFILE ON)

set(SOURCE_FILES main.cpp ctbpos.cpp TemplatesFromTree.cpp TreeNode.cpp Triple.cpp ComputeSimilarity.cpp InferenceFromTemplate.cpp InferenceFromTemplate.h)
add_executable(DIRT ${SOURCE_FILES})