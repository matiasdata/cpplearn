#include "FileSystem_unsafe.h"
#include <iostream>

FileSystem::FileSystem()
{
    std::cout << "FileSystem constructed!\n";
}

std::size_t FileSystem::numDisks() const
{
    return 1; // Dummy implementation
}

FileSystem tfs; // definition of tfs