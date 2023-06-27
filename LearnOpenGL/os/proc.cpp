#ifdef _WIN32
#include <windows.h>
#endif
#include "proc.h"

namespace os
{
    std::string curProcessLoc()
    {
#ifdef _WIN32
        char path[1024];
        GetModuleFileName(nullptr, path, sizeof(path));
        return path;
#else
        // linux, todo
        return "";
#endif
    }
}