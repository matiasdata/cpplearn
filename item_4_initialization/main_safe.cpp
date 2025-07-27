#include "Directory_safe.h"
#include <iostream>

int main()
{
    std::cout << "Main started.\n";
    tempDir(); // creates a directory
    return 0;
}

/*
If compiled it prints:
FileSystem constructed!
Directory constructed using 1disks.
Main started.

But it might also crash or get garbage output, 
depending on how tempDir and tfs are ordered by the linker. 
The initialization order of these non-local static variables is undefined.

*/