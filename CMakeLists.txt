cmake_minimum_required(VERSION 3.8)
project(probrem3_Particlefilter)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Particle.cpp Particle.h parameter.h Ensemble.cpp Ensemble.h Landmarks.cpp Landmarks.h random.cpp)
add_executable(probrem3_Particlefilter ${SOURCE_FILES})