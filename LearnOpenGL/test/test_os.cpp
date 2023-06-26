#include "proc.h"
#include <iostream>

namespace test
{
    void os()
    {
        std::cout << "process path:" << os::curProcessLoc() << std::endl;
    }
}