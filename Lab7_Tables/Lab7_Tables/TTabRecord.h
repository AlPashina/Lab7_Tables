#pragma once
#include <string>
#include <iostream>
#include "TDatValue.h"

typedef std::string TKey;
class TTabRecord;
typedef TTabRecord* PTTabRecord;

class TTabRecord : public TDatValue {
protected:
    TKey Key;
    PTDatValue pValue;
    virtual void Print()
    {
        std::cout << Key << " " << pValue->ToString() << std::endl;
    }
public:
    TTabRecord(TKey key, PTDatValue Val) : Key(key), pValue(Val) {};
    void SetKey(TKey k) { Key = k; }
    TKey GetKey() { return Key; }
    void SetValue(PTDatValue p) { pValue = p; }
    PTDatValue GetValue() { return pValue; }
    virtual TDatValue* GetCopy() { return new TTabRecord(Key, pValue); }
    TTabRecord& operator=(TTabRecord& tr) { Key = tr.Key; pValue = tr.pValue; return *this; }
    virtual bool operator==(const TTabRecord& tr) { return Key == tr.Key; }
    virtual bool operator<(const TTabRecord& tr) { return Key < tr.Key; }
    virtual bool operator>(const TTabRecord& tr) { return Key > tr.Key; }
    virtual std::string ToString() override {
        // //    std::string res = this->GetKey() + "   " + (this->GetValue()->ToString());
             //return nullptr;
        return this->GetKey();
    }
    friend class TArrayTable;
    friend class TScanTable;
    friend class TSortTable;
    friend class TTreeNode;
    friend class TTreeTable;
    friend class TArrayHash;
    friend class TListHash;
};

