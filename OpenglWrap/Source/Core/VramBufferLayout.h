#pragma once
#include <vector>

class VramBufferLayout
{
	friend class LaidVramBuffer;
	struct VariableInfo
	{
		unsigned Type;
		unsigned Count;
		unsigned Size;
		bool Normalized = true;
	};
public:
	VramBufferLayout& Float(unsigned count);
	VramBufferLayout& Int(unsigned count);
	VramBufferLayout& Unsigned(unsigned count);


private:
	std::vector<VariableInfo> Variables;
	unsigned Size = 0;
};
