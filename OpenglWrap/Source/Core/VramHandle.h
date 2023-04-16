#pragma once

class VramHandle
{
public:
	VramHandle() = default;
	virtual ~VramHandle() = default;

	operator bool() const;
	int GetHandle() const
	{
		return _handle;
	}

	virtual bool Init();
	virtual void Destroy();


protected:
	void SetHandle(int handle, bool bNotExistsOnly = false);

	virtual int AllocateVram() = 0;
	virtual void DeallocateVram() = 0;


private:
	int _handle = 0;
};
