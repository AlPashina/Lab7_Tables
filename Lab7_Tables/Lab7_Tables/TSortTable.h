#pragma once
#include "TScanTable.h"

enum TSortMethod {QUIQ, INSERT, MERGE};
class  TSortTable : public TScanTable {
protected:
    TSortMethod SortMethod;
    void SortData();
    void InsertSort(PTTabRecord* pMem, int DataCount);
    void MergeSort(PTTabRecord* pMem, int DataCount);
    void MergeSorter(PTTabRecord*& pData, PTTabRecord*& pBuff, int size);
    void MergeData(PTTabRecord*& pData, PTTabRecord*& pBuff, int n1, int n2);
    void QuickSort(PTTabRecord* pMem, int DataCount);
    void QuickSplit(PTTabRecord* pData, int size, int& pivot);

public:
    TSortTable(int Size = 20) : TScanTable(Size) {};
    TSortTable(const TScanTable& tab);
    TSortTable& operator=(const TScanTable& tab);
    TSortMethod GetSortMethod(void);
    void SetSortMethod(TSortMethod sm);
    virtual PTDatValue FindRecord(TKey key);
    virtual void InsRecord(TKey k, PTDatValue pVal);
    virtual void DelRecord(TKey k);
   
};
