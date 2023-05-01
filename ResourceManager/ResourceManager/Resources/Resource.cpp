#include "Resource.h"


Resource::Resource(const ResourceDesc& desc):
    _desc(desc)
{
}

Resource::~Resource()
{
}

bool Resource::Load(std::istream& stream, bool forceUpdate)
{
    if (forceUpdate || !_isLoaded)
    {
        _isLoaded = LoadImpl(stream);
    }

    return _isLoaded;
}

void Resource::Save(std::ostream& stream)
{
    SaveImpl(stream);
}

void Resource::SaveOnDestroy(bool state)
{
    _saveOnDestroy = state;
}

void Resource::Unload()
{
    if (_isLoaded)
        UnloadImpl();

    _isLoaded = false;
}
