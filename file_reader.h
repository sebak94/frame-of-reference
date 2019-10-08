#ifndef __FILE_READER_H__
#define __FILE_READER_H__

#include <fstream>
#include <stdint.h>
#include <vector>
#include <string>
#include <mutex>

// Wrapper de fstream para leer del archivo
class FileReader {
    private:
    std::fstream fs;
    std::mutex m;

    public:
    explicit FileReader(const std::string filename);
    // Posiciona, lee y devuelve el tamaño leído, siendo como máximo size,
    // haciendo un lock antes. Lo leído se guarda en block
    size_t seekg_read_and_gcount(char *block, size_t size, size_t pos);
    // Devuelve la longitud del archivo abierto
    size_t glength();
    // Devuelve si hubo errores en la última operación
    int error();
    ~FileReader();
};

#endif
