#include <windows.h>
#include "proc.h"

namespace os
{
    std::string curProcessLoc()
    {
        char path[1024];
        GetModuleFileName(nullptr, path, sizeof(path));
        return path;
    }

}