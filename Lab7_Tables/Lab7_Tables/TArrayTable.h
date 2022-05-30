#pragma once
#include "TTabRecord.h"
#include "TTable.h"

enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class TArrayTable : public TTable {
protected:
	PTTabRecord* pRecs;
	int TabSize;
	int CurPos;
public:
	TArrayTable(int size = 100);
	virtual ~TArrayTable();
	virtual bool IsFull() const;
	int GetTabSize() const;
	virtual PTDatValue GetValue() const;
	virtual TKey GetKey()const;
	virtual TKey GetKey(TDataPos mode)const;
	virtual PTDatValue GetValue(TDataPos mode) const;
	virtual PTDatValue FindRecord(TKey k) = 0;
	virtual void InsRecord(TKey k, PTDatValue pVal) = 0;
	virtual void DelRecord(TKey k) = 0;
	bool Reset();
	virtual bool IsTabEnded() const;
	bool GoNext();
	int GetCurPos() const;
	virtual bool SetCurPos(int pos);
	friend class TSortTable;
};
