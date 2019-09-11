set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
cmake_minimum_required(VERSION 3.2)
project(SimpleGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Physics.cpp Physics.h Vec2.cpp Vec2.h RigidBody.cpp RigidBody.h Shape.cpp Shape.h Material.cpp Material.h Graphics.cpp Graphics.h Force.cpp Force.h ResourceManager.cpp ResourceManager.h Collision.cpp Collision.h)
add_executable(SimpleGame ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SimpleGame ${SFML_LIBRARIES})
endif()