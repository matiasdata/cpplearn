#pragma once
#include <cstddef>

class FileSystem
{
public:
    FileSystem();
    std::size_t numDisks() const;
};

extern FileSystem tfs; 

// declared here but defined elsewhere (not defined yet).
// used to shared global variables across different translation units (source files).