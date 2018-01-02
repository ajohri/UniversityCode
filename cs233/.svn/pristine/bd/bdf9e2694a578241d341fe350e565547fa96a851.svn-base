#include "cacheblock.h"

uint32_t Cache::Block::get_address() const {

  uint32_t tag = get_tag();
  uint32_t index = _index;
  uint32_t indexBits = _cache_config.get_num_index_bits();
  uint32_t offsetBits = _cache_config.get_num_block_offset_bits();

  tag = (tag << indexBits);
  tag = tag | index;
  tag = (tag << offsetBits);
  return tag;
}
