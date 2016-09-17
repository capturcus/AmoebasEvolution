cmake_minimum_required(VERSION 3.6)
project(AmoebasEvolution)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 COMPONENTS system window graphics REQUIRED)
find_package(Box2D REQUIRED)
set(SOURCE_FILES main.cpp Amoeba.cpp Amoeba.h main.h AmoebaFood.cpp AmoebaFood.h AmoebaWorld.cpp AmoebaWorld.h)
add_executable(AmoebasEvolution ${SOURCE_FILES})
target_link_libraries(AmoebasEvolution ${BOX2D_LIBRARIES} ${SFML_LIBRARIES} Box2D)