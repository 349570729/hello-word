#define GLM_FORCE_SWIZZLE
#include "glm/glm.hpp"
#include <iostream>
#include "glm_demo.h"

void printVec4(const glm::vec4 &v4)
{
    std::cout << "vec4: " << v4.x << v4.y << v4.z << v4.w << std::endl;
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

void glm_main()
{
    demo1();
}