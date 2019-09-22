#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdio.h>
#include <stdint.h>

uint8_t number_of_bits(uint32_t value);
uint32_t minimum(uint32_t valueA, uint32_t valueB);
uint32_t maximum(uint32_t valueA, uint32_t valueB);
uint32_t minimum_in_array(uint32_t *array, size_t length);

#endif
