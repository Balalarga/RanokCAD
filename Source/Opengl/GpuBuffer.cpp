#include "GpuBuffer.h"
#include <cassert>

GpuBufferLayout& GpuBufferLayout::Float(unsigned int count) {
	_variables.push_back({ .Type = GL_FLOAT, .Num = count, .Size = sizeof(GLfloat) });
	_totalSize += count * sizeof(GLfloat);
	return *this;
}

GpuBufferLayout& GpuBufferLayout::Int(unsigned int count) {
	_variables.push_back({ .Type = GL_INT, .Num = count, .Size = sizeof(GLint) });
	_totalSize += count * sizeof(GLint);
	return *this;
}

GpuBufferLayout& GpuBufferLayout::Unsigned(unsigned int count) {
	_variables.push_back({ .Type = GL_UNSIGNED_INT, .Num = count, .Size = sizeof(GLuint) });
	_totalSize += count * sizeof(GLuint);
	return *this;
}

const std::vector<GpuBufferLayout::Variable>& GpuBufferLayout::GetVariables() const {
	return _variables;
}

unsigned GpuBufferLayout::GetSize() const {
	return _totalSize;
}


TransferDataPtr TransferDataPtr::Empty = TransferDataPtr(nullptr, 0, 0);

TransferDataPtr::TransferDataPtr(void* inPtr, unsigned inCount, unsigned inItemSize): Ptr(inPtr),
	Count(inCount),
	ItemSize(inItemSize) {
}


GpuBuffer::GpuBuffer(Gpu::BufferType type, Gpu::BufferUsageMode mode): _type(type), _mode(mode) {
}

GpuBuffer& GpuBuffer::SetData(const TransferDataPtr& data) {
	_data = data;
	return *this;
}

const TransferDataPtr& GpuBuffer::GetData() const {
	return _data;
}

GpuBuffer& GpuBuffer::SetLayout(GpuBufferLayout&& layout) {
	assert(!IsValid());

	_layout = std::move(layout);
	return *this;
}

const GpuBufferLayout& GpuBuffer::GetLayout() const {
	return _layout;
}

std::optional<GpuBuffer::THandle> GpuBuffer::CreateHandle() {
	unsigned handle;
	glGenBuffers(1, &handle);
	glBindBuffer(static_cast<std::underlying_type_t<Gpu::BufferType>>(_type), handle);
	glBufferData(
		static_cast<std::underlying_type_t<Gpu::BufferType>>(_type),
		_data.Count * _data.ItemSize,
		_data.Ptr,
		static_cast<std::underlying_type_t<Gpu::BufferUsageMode>>(_mode));

	const std::vector<GpuBufferLayout::Variable>& layoutVars = _layout.GetVariables();
	const auto layoutSize = static_cast<GLsizei>(_layout.GetSize());
	unsigned offset = 0;
	for (int i = 0; i < layoutVars.size(); ++i) {
		const auto& [Type, Num, Size, Normalized] = layoutVars[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(
			i,
			static_cast<GLint>(Num),
			Type,
			Normalized,
			layoutSize,
			reinterpret_cast<void*>(offset));

		offset += Size * Num;
	}
	return handle;
}

void GpuBuffer::DestroyHandle(THandle handle) {
	const unsigned* a = &handle;
	glDeleteBuffers(1, a);
}