#ifndef __FILE_H__
#define __FILE_H__

#include <fstream>
#include <stdint.h>
#include <vector>

class File {
    protected:
    std::fstream fs;

    public:
    File(const char *filename, std::ios_base::openmode mode);
    void read(char *block, size_t size);
    void write(const char *block, size_t size);
    int glength();
    int gcount();
    int error();
    int eof();
    ~File();
};

#endif
