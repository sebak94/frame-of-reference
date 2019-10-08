#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdio.h>
#include <stdint.h>

// Devuelve la cantidad de bits necesarios para representar a value
uint8_t number_of_bits(uint32_t value);
// Devuelve el mínimo entre dos números
uint32_t minimum(uint32_t valueA, uint32_t valueB);
// Devuelve el máximo entre dos números
uint32_t maximum(uint32_t valueA, uint32_t valueB);
// Devuelve el número mínimo de un array con longitud length
uint32_t minimum_in_array(uint32_t *array, size_t length);

#endif
