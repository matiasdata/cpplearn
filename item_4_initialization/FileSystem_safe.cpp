
#include "FileSystem_safe.h"
#include <iostream>

FileSystem::FileSystem()
{
    std::cout << "FileSystem constructed!\n";
}

std::size_t FileSystem::numDisks() const
{
    return 1; // Dummy implementation
}

FileSystem& tfs()
{
    static FileSystem fs;
    return fs;
}