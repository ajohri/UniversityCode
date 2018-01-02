#include "cacheconfig.h"
#include "utils.h"
#include "math.h"

CacheConfig::CacheConfig(uint32_t size, uint32_t block_size, uint32_t associativity)
: _size(size), _block_size(block_size), _associativity(associativity) {

	uint32_t blocks = _size / _block_size;
	_num_block_offset_bits = (uint32_t) log2(_block_size);
	uint32_t sets = blocks / _associativity;
	_num_index_bits = (uint32_t) log2(sets);

	_num_tag_bits = 32 - _num_index_bits - _num_block_offset_bits; 
}
