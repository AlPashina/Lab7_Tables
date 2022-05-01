#pragma once
#include "TTabRecord.h"
#include "TDataCom.h"
#define DataOk 0
#define TabEmpty -101
#define TabFull -102
#define TabNoRecord -104
#define TabNoMem -105

class TTable: TDataCom {
protected:
    int DataCount; 
    int Efficiency; 
    TTable() { DataCount = 0; Efficiency = 0; } 
    virtual ~TTable() {};
    int GetDataCount() const { return DataCount; }    
    int GetEfficiency() const { return Efficiency; }
    int IsEmpty() const { return DataCount == 0; }   
    virtual bool IsFull() const = 0;                 
    virtual PTDatValue FindRecord(TKey k) = 0; 
    virtual void InsRecord(TKey k, PTDatValue pVal) = 0; 
    virtual void DelRecord(TKey k) = 0;      
    virtual int Reset() = 0;
    virtual int GoNext() = 0;
    virtual bool IsTabEnded() const = 0; 
    virtual TKey GetKey() const = 0;
    virtual PTDatValue GetValue() const = 0;

    friend std::ostream& operator << (std::ostream& os, TTable& tab) {
        for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext()) 
            os << "Key: " << tab.GetKey()<< " Val: " << tab.GetValue() << std::endl;
        return os;
    }
};
