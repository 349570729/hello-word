#ifndef PROC_H
#define PROC_H

#include <string>

#define OS_NAMESPACE_BEGIN namespace os {
#define OS_NAMESPACE_END }


OS_NAMESPACE_BEGIN 
    std::string curProcPath();
    std::string curProcDir();
OS_NAMESPACE_END

#endif // PROC_H