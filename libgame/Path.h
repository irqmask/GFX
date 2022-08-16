#pragma once

#include <string>

class Path;

/// Container storing file paths.
class Path
{
public:
    Path(const std::string &path = "");
    
    static Path fromCurrentExecutable();
    
    std::string plusFilename(const std::string &filename);
    Path plusPath(const std::string &path);
    std::string toString();

    
private:
        std::string m_path;
};