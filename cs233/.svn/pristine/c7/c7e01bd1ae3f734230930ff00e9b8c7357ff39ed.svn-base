#include "simplecache.h"

int SimpleCache::find(int index, int tag, int block_offset) {
	for( auto &pos : _cache[index])
	{
		if(pos.tag() == tag && pos.valid())
		{
			return pos.get_byte(block_offset);
		}
	}

	// read handout for implementation details
  return 0xdeadbeef;
}

void SimpleCache::insert(int index, int tag, char data[]) {
	for( auto &pos : _cache[index])
	{
		if(!pos.valid())
		{
			pos.replace(tag, data);
			return;
		}
	}
	_cache[index][0].replace(tag,data);
	return;

// read handout for implementation details
}
