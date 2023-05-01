#pragma once
#include <type_traits>

class VramHandle
{
public:
	VramHandle() = default;
	virtual ~VramHandle() = default;

	int GetHandle() const
	{
		return _handle;
	}

	virtual bool Construct(bool bForce = false);
	virtual void Destroy();

	virtual bool IsValid() const
	{
		return _handle != 0;
	}


protected:
	virtual bool PreInit();
	virtual bool Init();
	virtual bool PostInit();

	virtual int AllocateVram() = 0;
	virtual void DeallocateVram() = 0;


private:
	int _handle = 0;
};

template<class T, class... TArgs>
requires std::is_base_of_v<VramHandle, T>
class AutoConstructor
{
public:
	static AutoConstructor Create(TArgs&&... args)
	{
		return AutoConstructor(std::forward<TArgs>(args)...);
	}

	~AutoConstructor()
	{
		Instance.Destroy();
	}

	T& Get()
	{
		return Instance;
	}

	T& operator*()
	{
		return Get();
	}

	bool IsValid() const
	{
		return Instance.IsValid();
	}

	operator bool()
	{
		return IsValid();
	}

	operator T&()
	{
		return Get();
	}

	operator T()
	{
		return AutoConstructor(Instance);
	}


private:
	AutoConstructor(TArgs&&... args) : Instance(std::forward<TArgs>(args)...)
	{
		Instance.Construct();
	}

	AutoConstructor(const T& inst) : Instance(inst)
	{
		Instance.Construct();
	}

	T Instance;
};
