#define GLM_FORCE_SWIZZLE
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "glm_demo.h"

void printVec4(const glm::vec4 &v4)
{
    std::cout << "vec4: " << v4.x << v4.y << v4.z << v4.w << std::endl;
}

void printMat4(const glm::mat4 &m4)
{
    for (int i = 0; i < 4; ++i)
    {
        printVec4(m4[i]);
    }
}

void demo1()
{
    glm::vec4 v4(1.0f, 2.0f, 3.0f, 1.0f);
    printVec4(v4);

    // Swizzle operators, must enable GLM_FORCE_SWIZZLE macro
    glm::vec4 v4_xyzw = v4.yxwz;
    printVec4(v4_xyzw);
    glm::vec4 v4_rgba = v4.grab;
    printVec4(v4_rgba);

    // v4.rgba() = (5.0f, 6.0f, 7.0f, 8.0f);
    // std::cout << "v4.r: " << v4.r << std::endl;
    v4.r = 5.0f;
    std::cout << "v4.r: " << v4.r << std::endl;
}

void demo2()
{
    glm::vec4 v4(1.0f, 2.0f, 3.0f, 1.0f);
    // trans,rotate... is default initialized as a unit matrix
    glm::mat4 trans, rotate, scale;
    std::cout << "initial matrix" << std::endl;
    printMat4(trans);
    // construct a matrix based on param1, add move transform
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    // construct a matrix, rotate around param3 at param2 degrees
    rotate = glm::rotate(rotate, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    // scale
    scale = glm::scale(scale, glm::vec3(0.5f, 2.0f, 0.0f));
    std::cout << "trans matrix" << std::endl;
    printMat4(trans);
    std::cout << "rotate matrix" << std::endl;
    printMat4(rotate);
    std::cout << "scale matrix" << std::endl;
    printMat4(scale);

    std::cout << "trans vec" << std::endl;
    printVec4(trans * v4);
}

void glm_main()
{
    demo2();
}