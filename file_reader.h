#ifndef __FILE_READER_H__
#define __FILE_READER_H__

#include <fstream>
#include <stdint.h>
#include <vector>
#include <string>
#include <mutex>

class FileReader {
    private:
    std::fstream fs;
    std::mutex m;

    public:
    explicit FileReader(const std::string filename);
    size_t seekg_read_and_gcount(char *block, size_t size, size_t pos);
    size_t glength();
    int error();
    ~FileReader();
};

#endif
