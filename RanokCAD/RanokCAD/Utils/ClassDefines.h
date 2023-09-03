#pragma once

#define DefineGetter(name, field)                                                                                      \
	auto Get##name() const                                                                                             \
	{                                                                                                                  \
		return field;                                                                                                  \
	}

#define DefineSetter(name, inType, field)                                                                              \
	void Set##name(inType newValue)                                                                                    \
	{                                                                                                                  \
		field = static_cast<decltype(field)>(newValue);                                                                \
	}

#define DefineNamedSetter(name, inType, field)                                                                         \
	void Set##name(inType newValue)                                                                                    \
	{                                                                                                                  \
		field = static_cast<decltype(field)>(newValue);                                                                \
	}

#define DefineConstructSetter(name, inType, field)                                                                     \
	auto Set##name(inType newValue)                                                                                    \
	{                                                                                                                  \
		field = static_cast<decltype(field)>(newValue);                                                                \
		return *this;                                                                                                  \
	}