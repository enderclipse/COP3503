cmake_minimum_required(VERSION 3.13)
project(EvoSim)

set(CMAKE_CXX_STANDARD 14)

add_executable(EvoSim main.cpp Creature.cpp Creature.h World.cpp World.h SimulationDriver.cpp SimulationDriver.h)