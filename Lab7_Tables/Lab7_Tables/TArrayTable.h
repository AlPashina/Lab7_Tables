#pragma once
#include "TTabRecord.h"
#include "TTable.h"
#define TabMaxSize 25;

enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class TArrayTable : public TTable {
protected:
    PTTabRecord* pRecs; 
    int TabSize;        
    int CurPos;        
public:
    TArrayTable(int size = 100) :TabSize(size) {
        pRecs = new PTTabRecord[TabSize];
        for (int i = 0; i < TabSize; i++) {
            pRecs[i] = 0;
        }
        CurPos = 0;
    };
    virtual ~TArrayTable() {
        for (int i = 0; i < TabSize; i++) {
            delete pRecs[i];
        }
        delete[]pRecs;
    };        

    virtual bool IsFull() const {
        return DataCount >= TabSize;
    }   
    int GetTabSize() const {
        return TabSize;
    }
    virtual PTDatValue GetValuePtr() const{ 
        return GetValuePtr(CURRENT_POS); }
	virtual TKey GetKey(TDataPos mode)const {
		int pos = -1;
		if (!IsEmpty()) {
			switch (mode)
			{
			case FIRST_POS:
				pos = 0;
				break;
			case LAST_POS:
				pos = DataCount - 1;
				break;
			default:
				pos = CurPos;
				break;
			}
		}
		return (pos == -1) ? std::string("") : pRecs[pos]->Key;
	}
	virtual PTDatValue GetValuePtr(TDataPos mode) const {
		int pos = -1;
		if (!IsEmpty()) {
			switch (mode)
			{
			case FIRST_POS:
				pos = 0;
				break;
			case LAST_POS:
				pos = DataCount - 1;
				break;
			default:
				pos = CurPos;
				break;
			}
		}
		return (pos == -1) ? nullptr : pRecs[pos]->pValue;
	}
    virtual PTDatValue FindRecord(TKey k) = 0; 
    virtual void InsRecord(TKey k, PTDatValue pVal) = 0; 
    virtual void DelRecord(TKey k) = 0;       
	bool Reset() {
		CurPos = 0;
		return IsTabEnded();
	}
    virtual bool IsTabEnded() const {
		return CurPos >= TabSize;
	}
	bool GoNext() {
		if (!IsTabEnded())
			CurPos++;
		return IsTabEnded();
	}
	int GetCurPos() const {
		return CurPos;
	}
	virtual bool SetCurPos(int pos) {
		CurPos = ((pos > -1) && (pos < DataCount)) ? pos : 0;
		return IsTabEnded();
	}
    friend class TSortTable;
};
