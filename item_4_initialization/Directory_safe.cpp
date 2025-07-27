#include "Directory_safe.h"
#include "FileSystem_safe.h"
#include <iostream>

Directory::Directory() : disks{tfs().numDisks()}
{
    std::cout << "Directory constructed using " << disks << " disks.\n";
}

Directory& tempDir()
{
    static Directory dir;
    return dir; 
}