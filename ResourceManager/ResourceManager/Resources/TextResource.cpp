#include "TextResource.h"

#include <istream>
#include <sstream>

Resource* TextResource::GetPrototype(const ResourceDesc& desc)
{
	return new TextResource(desc);
}

std::string TextResource::GetResourceType()
{
	return "Text";
}

bool TextResource::LoadImpl(std::istream& stream)
{
	std::stringstream strStream;
	strStream << stream.rdbuf();
	_data = strStream.str();
	return stream.good();
}

void TextResource::SaveImpl(std::ostream& stream)
{
	stream << _data;
}

void TextResource::UnloadImpl()
{
	_data.clear();
}