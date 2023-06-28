#ifdef _WIN32
#include <windows.h>
#define SEPERATOR "\\"
#else
#define SEPERATOR "/"
#endif
#include "proc.h"

namespace os
{
    std::string curProcLoc()
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
    std::string curProcDir()
    {
        std::string proc_loc = curProcLoc();
        return proc_loc.substr(0, proc_loc.find_last_of(SEPERATOR));
    }
}