cmake_minimum_required(VERSION 3.8)

project(learnOGL VERSION 0.1 LANGUAGES CXX)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE_LOWER)
set(DEST_DIR ${CMAKE_BINARY_DIR}/target/${BUILD_TYPE_LOWER})
message("DEST_DIR: ${DEST_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${DEST_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${DEST_DIR})

file(GLOB_RECURSE SRC src/*)
file(GLOB_RECURSE OS_SRC os/*)
file(GLOB_RECURSE UTIL_SRC utils/*)
file(GLOB_RECURSE TEST_SRC test/*)
file(GLOB RESOURCE_FILES res/*)
# message("RESOURCE_FILES: ${RESOURCE_FILES}")
file(COPY ${RESOURCE_FILES} DESTINATION ${DEST_DIR})

add_executable(${PROJECT_NAME} 
    ${SRC}
    ${OS_SRC}
    ${TEST_SRC}
    ${UTIL_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE
./include/
./include/glad
./include/GLFW
./include/KHR
./include/Shader
./include/stb
./include/tex
./include/triangle
./include/transform
./include/camera
./include/light
os
utils
./thirdparty/glm
)

if (UNIX)
    target_link_directories(${PROJECT_NAME} PRIVATE
        ./lib/linux)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        glfw
        ${CMAKE_DL_LIBS}
        pthread)
else()
# windows
    target_link_directories(${PROJECT_NAME} PRIVATE
        ./lib/win)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        glfw3
        Kernel32)
endif()

# target_link_libraries(${PROJECT_NAME} PRIVATE shell32)