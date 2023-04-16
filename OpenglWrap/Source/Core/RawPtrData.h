#pragma once
#include <vector>

class RawPtrData
{
public:
	RawPtrData(const void* ptr, unsigned count, unsigned itemSize):
		Ptr(ptr),
		Count(count),
		ItemSize(itemSize)
	{
	}

	template<class T>
	RawPtrData(const std::vector<T>& items):
		RawPtrData(static_cast<const void*>(&items[0]), items.size(), sizeof(T))
	{}

	template<class T>
	RawPtrData(const std::initializer_list<T>& items):
		RawPtrData(static_cast<void*>(&items[0]), items.size(), sizeof(T))
	{}


	const void* Ptr;
	const unsigned Count;
	const unsigned ItemSize;
};
