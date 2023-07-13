#ifdef _WIN32
#include <windows.h>
#define SEPERATOR "\\"
#else
#include <unistd.h>
#define SEPERATOR "/"
#endif
#include "proc.h"
#include <iostream>


OS_NAMESPACE_BEGIN
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
        char path[512];
        // refer to qt's impl qcoreapplication.cpp::qAppFileName()
        ssize_t len = readlink("/proc/self/exe", path, sizeof(path));
        if (len == sizeof(path)){
            std::cout << "Path is too long! Expect less than 512" << std::endl;
        }
        return path;
#endif
    }
    std::string curProcDir()
    {
        std::string proc_loc = curProcPath();
        return proc_loc.substr(0, proc_loc.find_last_of(SEPERATOR));
    }
OS_NAMESPACE_END
