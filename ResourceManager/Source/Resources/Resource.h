#pragma once

#include <string>

#include "ResourceDesc.h"


class Resource
{
public:
    Resource(const ResourceDesc& desc);
    virtual ~Resource();

    const ResourceDesc& GetDesc() const { return _desc; }
    bool IsLoaded() const { return _isLoaded; }

    void SaveOnDestroy(bool state);
    bool IsSaveOnDestroy() const { return _saveOnDestroy; }

    bool Load(std::istream& stream, bool forceUpdate = false);
    void Unload();
    void Save(std::ostream& stream);

    virtual std::string GetResourceType() = 0;
    virtual Resource* GetPrototype(const ResourceDesc& desc) = 0;


protected:
    virtual bool LoadImpl(std::istream& stream) = 0;
    virtual void SaveImpl(std::ostream& stream) = 0;
    virtual void UnloadImpl() = 0;


private:
    const ResourceDesc _desc;

    bool _isLoaded = false;
    bool _saveOnDestroy = false;
};
