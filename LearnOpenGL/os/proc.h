#ifndef PROC_H
#define PROC_H

#include <string>

namespace os
{
    std::string curProcPath();
    std::string curProcDir();
    std::string exeCmd(const std::string &cmd);
}

#endif // PROC_H