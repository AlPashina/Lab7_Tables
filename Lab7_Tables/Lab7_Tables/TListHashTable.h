#pragma once
#include "THashTable.h"
#include "TTabRecord.h"
#include <list>
class TListHashTable :public THashTable {
protected:
	int TabSize;
	int CurList;
	std::list  <PTTabRecord>* pList;
	std::list<PTTabRecord>::iterator startChain;
public:
	TListHashTable(int size);
	virtual ~TListHashTable()  override;
	virtual bool IsFull()const  override;
	virtual PTDatValue FindRecord(TKey k) override;
	virtual void InsRecord(TKey k, PTDatValue pVal) override;
	virtual void DelRecord(TKey key) override;
	virtual TKey GetKey() const override;
	virtual PTDatValue GetValue() const override;
	virtual bool Reset() override;
	virtual bool GoNext() override;
	virtual bool IsTabEnded()const override;
};