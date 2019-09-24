#ifndef __FILE_H__
#define __FILE_H__

#include <fstream>
#include <stdint.h>
#include <vector>
#include <string>
#include <mutex>

class File {
    protected:
    std::fstream fs;
    std::mutex m;

    public:
    File(const std::string filename, std::ios_base::openmode mode);
    size_t seekg_read_and_gcount(char *block, size_t size, size_t pos);
    void write(const char *block, size_t size);
    size_t glength();
    int error();
    ~File();
};

#endif
