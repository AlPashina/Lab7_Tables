#pragma once
#include "TTable.h"

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
    ~TArrayTable() {
        for (int i = 0; i < TabSize; i++) {
            delete pRecs[i];
        }
        delete[]pRecs;
    };        

    virtual int IsFull() const override; 
    int GetTabSize() const;     
    virtual TKey GetKey() const override;
    virtual PTDatValue GetValuePtr() const override;
    virtual TKey GetKey(TDataPos mode) const;
    virtual PTDatValue GetValuePtr(TDataPos mode) const;
    virtual PTDatValue FindRecord(TKey k) = 0; 
    virtual void InsRecord(TKey k, PTDatValue pVal) = 0; 
    virtual void DelRecord(TKey k) = 0;       
    virtual int Reset() override;   
    virtual int IsTabEnded() const override; 
    virtual int GoNext() override; 
    virtual int SetCurrentPos(int pos);
    int GetCurrentPos() const;     
    friend class TSortTable;
};
