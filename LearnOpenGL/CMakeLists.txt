cmake_minimum_required(VERSION 3.8)

project(LearnOGL VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE PROJECT_SOURCES . *.cpp *.c *.h)
file(GLOB RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/res/*)
message("RESOURCE_FILES: ${RESOURCE_FILES}")
file(COPY ${RESOURCE_FILES} DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})

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

if (UNIX) 
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        glfw
        ${CMAKE_DL_LIBS})
else()
# windows
    target_link_directories(${PROJECT_NAME} PRIVATE
        ./lib/win)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw3)
endif()

# target_link_libraries(${PROJECT_NAME} PRIVATE shell32)