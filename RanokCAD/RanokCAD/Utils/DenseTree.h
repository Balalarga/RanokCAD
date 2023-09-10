#pragma once
#include <functional>
#include <map>


template <class TKey, class TValue>
class DenseTree
{
public:
	enum class WalkResult
	{
		Continue,
		Break,
		Stop,
	};

	void Add(TKey&& key, TValue&& val)
	{
		_subtree.try_emplace(key, val);
	}

	std::map<TKey, DenseTree>& GetSubtree()
	{
		return _subtree;
	}

	const std::map<TKey, DenseTree>& GetSubtree() const
	{
		return _subtree;
	}

	const TValue& Get() const
	{
		return _value;
	}

	TValue& operator*()
	{
		return _value;
	}

	TValue& operator->()
	{
		return _value;
	}

	void Walk(const std::function<WalkResult(const TKey&, const TValue&)>& iterator)
	{
		WalkImpl(iterator);
	}


protected:
	WalkResult WalkImpl(const std::function<WalkResult(const TKey&, const TValue&)>& iterator)
	{
		for (auto& [key, val] : _subtree)
		{
			WalkResult res = iterator(key, *val);
			if (res == WalkResult::Continue)
				res = val.WalkImpl(iterator);

			if (res == WalkResult::Stop)
				return res;
			
			if (res == WalkResult::Break)
				break;
		}

		return WalkResult::Continue;
	}


private:
	TValue _value;
	std::map<TKey, DenseTree> _subtree;
};
