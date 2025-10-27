#include "Directory_unsafe.h"
#include "FileSystem_unsafe.h"
#include <iostream>

Directory::Directory() : disks{tfs.numDisks()}
{
    std::cout << "Directory constructed using " << disks << " disks.\n";
}

Directory tempDir;