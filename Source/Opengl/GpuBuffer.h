#pragma once

#include <vector>
#include "GpuResource.h"


namespace Gpu {
enum class BufferType: unsigned {
	Array        = GL_ARRAY_BUFFER,
	ElementArray = GL_ELEMENT_ARRAY_BUFFER,
	CopyRead     = GL_COPY_READ_BUFFER,
	CopyWrite    = GL_COPY_WRITE_BUFFER,
	Texture      = GL_TEXTURE_BUFFER,
	Uniform      = GL_UNIFORM_BUFFER,
	Query        = GL_QUERY_BUFFER
};

enum class BufferUsageMode: unsigned {
	StreamDraw  = GL_STREAM_DRAW,
	StreamRead  = GL_STREAM_READ,
	StreamCopy  = GL_STREAM_COPY,
	StaticDraw  = GL_STATIC_DRAW,
	StaticRead  = GL_STATIC_READ,
	StaticCopy  = GL_STATIC_COPY,
	DynamicDraw = GL_DYNAMIC_DRAW,
	DynamicRead = GL_DYNAMIC_READ,
	DynamicCopy = GL_DYNAMIC_COPY
};
}


class GpuBufferLayout {
public:
	struct Variable {
		unsigned Type = 0;
		unsigned Num = 0;
		unsigned Size = 0;
		bool Normalized = true;
	};

	GpuBufferLayout& Float(unsigned count);
	GpuBufferLayout& Int(unsigned count);
	GpuBufferLayout& Unsigned(unsigned count);

	const std::vector<Variable>& GetVariables() const;
	unsigned GetSize() const;


private:
	std::vector<Variable> _variables;
	unsigned _totalSize = 0;
};


struct TransferDataPtr {
	static TransferDataPtr Empty;

	TransferDataPtr(void* ptr, unsigned count, unsigned itemSize);

	template<class T>
	explicit TransferDataPtr(const std::vector<T>& items): TransferDataPtr(
		static_cast<void*>(items.data()),
		items.size(),
		sizeof(T)) {
	}

	template<class T>
	TransferDataPtr(const std::initializer_list<T>& items): TransferDataPtr(
		static_cast<void*>(&items[0]),
		items.size(),
		sizeof(T)) {
	}

	void* Ptr;
	unsigned Count;
	unsigned ItemSize;
};


class GpuBuffer: public GpuResource {
public:
	GpuBuffer(Gpu::BufferType type, Gpu::BufferUsageMode mode);

	GpuBuffer& SetData(const TransferDataPtr& data);
	const TransferDataPtr& GetData() const;

	GpuBuffer& SetLayout(GpuBufferLayout&& layout);
	const GpuBufferLayout& GetLayout() const;


protected:
	std::optional<THandle> CreateHandle() override;
	void DestroyHandle(THandle handle) override;


private:
	Gpu::BufferType _type;
	Gpu::BufferUsageMode _mode;

	GpuBufferLayout _layout;
	TransferDataPtr _data = TransferDataPtr::Empty;
};