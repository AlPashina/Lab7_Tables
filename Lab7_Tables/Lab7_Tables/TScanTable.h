#pragma once
#include "TArrayTable.h"

class TScanTable :public TArrayTable {
public:
	TScanTable(int size = 25) :TArrayTable(size) { }
	virtual PTDatValue FindRecord(TKey k);
	virtual void InsRecord(TKey k, PTDatValue pVal);
	virtual void  DelRecord(TKey k);
	friend std::ostream& operator<<(std::ostream& os, TScanTable& tab);
};
