#include "utils.h"
#include <iostream>
uint32_t extract_tag(uint32_t address, const CacheConfig& cache_config) {

	uint32_t tagBits = cache_config.get_num_tag_bits();

	if(tagBits == 32) return address;
	if(tagBits == 0) return 0;

	return address >> (32 - tagBits);
}

uint32_t extract_index(uint32_t address, const CacheConfig& cache_config) {

	uint32_t indexBits = cache_config.get_num_index_bits();
	uint32_t tagBits = cache_config.get_num_tag_bits();

	if(indexBits == 32) return address;
	if(indexBits == 0) return 0;

	return (address << (tagBits)) >> (32 - indexBits);
}

uint32_t extract_block_offset(uint32_t address, const CacheConfig& cache_config) {

	uint32_t blockOffsetBits = cache_config.get_num_block_offset_bits();

	if(blockOffsetBits == 32) return address;
	if(blockOffsetBits == 0) return 0;

	return (address << (32 - blockOffsetBits)) >> (32- blockOffsetBits);
}
