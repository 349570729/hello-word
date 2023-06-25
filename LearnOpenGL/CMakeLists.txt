cmake_minimum_required(VERSION 3.8)

project(LearnOGL VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE PROJECT_SOURCES . *.cpp *.c *.h)
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src PROJECT_SOURCES)
# message("PROJECT_SOURCES: ${PROJECT_SOURCES}")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
# add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    ./include/
    ./include/glad
    ./include/GLFW
    ./include/KHR
    ./include/Shader
    ./include/stb
    ./include/tex
    ./include/triangle
)
target_link_directories(${PROJECT_NAME} PRIVATE
    ./lib
    )
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw
    ${CMAKE_DL_LIBS})
# target_link_libraries(${PROJECT_NAME} PRIVATE shell32)