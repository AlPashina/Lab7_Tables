#pragma once
#include <string>

class TDatValue;

typedef TDatValue* PTDatValue;

class TDatValue {
public:
	virtual TDatValue* GetCopy() = 0;
	virtual std::string ToString() = 0;
};