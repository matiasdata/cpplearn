#pragma once
#include <cstddef>

class Directory
{
public:
    Directory();
private:
    std::size_t disks;
};

Directory& tempDir();