#include "Path.h"

#include <algorithm>

#ifdef _WIN32
#include "Windows.h"
#define getcwd _getcwd
#else
#include <unistd.h>
#endif

#include "GameExceptions.h"

Path::Path(const std::string &rootpath)
{
    m_path = rootpath;

#if _WIN32
    // convert to unix-style path delimeters
    std::replace(m_path.begin(), m_path.end(), '\\', '/');
#endif

    // check for trailing path delimeter
    if (m_path.back() != '/') {
        m_path += '/';
    }
}


Path Path::fromCurrentExecutable()
{
    const unsigned long PATH_MAX_SIZE = 2048;
    char buf[PATH_MAX_SIZE + 1];
#ifdef _WIN32
    unsigned long len = GetModuleFileNameA(NULL, buf, PATH_MAX_SIZE);
    buf[PATH_MAX_SIZE] = '\0';

    if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
        throw BufferAllocFailed(LOC, "Path to Executable exceeds %d bytes!", PATH_MAX_SIZE);
    }
    if (len == 0) {
        throw OperationFailed(LOC, "Unable to get path to executable! OS error %d", GetLastError());
    }
#else
    ssize_t rc = readlink("/proc/self/exe", buf, PATH_MAX_SIZE);
    size_t len = 0;
    if (rc <= 1) {
        throw OperationFailed(LOC, "Unable to get path to executable!");
    } 
    else {
        len = rc;
    }
    if (len == 0) {
        throw OperationFailed(LOC, "Unable to get path to executable! OS error %d", errno);
    }
#endif

    std::string s(buf);

    // strip executable name
#ifdef _WIN32
    auto isPathDelimeter = [](char c)
    {
        return c == '\\';
    };
#else
    auto isPathDelimeter = [](char c)
    {
        return c == '/';
    };
#endif
    s.erase(std::find_if(s.rbegin(), s.rend(), isPathDelimeter).base(), s.end());

    return Path(s);
}


std::string Path::plusFilename(const std::string &filename)
{
    return m_path + filename;
}


Path Path::plusPath(const std::string& path)
{
    return Path(m_path + path);
}


std::string Path::toString()
{
    return plusFilename("");
}
