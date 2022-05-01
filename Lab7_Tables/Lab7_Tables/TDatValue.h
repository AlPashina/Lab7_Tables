#pragma once
#pragma once

class TDatValue;

typedef TDatValue* PTDataValue;

class TDatValue {
public:
	virtual TDatValue* GetCopy() = 0;
};