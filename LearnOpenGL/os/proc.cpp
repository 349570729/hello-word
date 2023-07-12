#ifdef _WIN32
#include <windows.h>
#define SEPERATOR "\\"
#else
#include <unistd.h>
#define SEPERATOR "/"
#endif
#include "proc.h"

namespace os
{
    std::string curProcPath()
    {
#ifdef _WIN32
        char path[1024];
        GetModuleFileName(nullptr, path, sizeof(path));
        return path;
#else
        // linux
        // getcwd: get current working directory, not process path
        // char *buffer = getcwd(NULL, 0);
        char cmd[64];
        // refer to qt's impl qcoreapplication.cpp::qAppFileName()
        int len = snprintf(cmd, sizeof(cmd), "realpath /proc/%d/exe", getpid());
        return exeCmd(cmd);
#endif
    }
    std::string curProcDir()
    {
        std::string proc_loc = curProcPath();
        return proc_loc.substr(0, proc_loc.find_last_of(SEPERATOR));
    }
    std::string exeCmd(const std::string &cmd)
    {
        // return cmd execute result
#ifdef _WIN32
        // todo
        return std::string();
#else
        return std::string();
#endif
    }
}