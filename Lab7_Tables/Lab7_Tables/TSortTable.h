#pragma once
#include "TArrayTable.h"
#include "TScanTable.h"

enum TSortMethod {  INSERT, MERGE,QUIQ };
class  TSortTable : public TScanTable {
protected:
    TSortMethod SortMethod;
    void SortData() {
        switch (SortMethod)
        {
        case INSERT:
            InsertSort(pRecs, DataCount);
            break;
        case MERGE:
            MergeSort(pRecs, DataCount);
            break;
        case QUIQ:
            QuickSort(pRecs, DataCount);
            break;
        }
    }
    void InsertSort(PTTabRecord* pMem, int DataCount) {
        PTTabRecord pR;
        Efficiency = DataCount;
        for (int i = 1, j; i < DataCount; i++)
        {
            pR = pRecs[i];
            for (j = i - 1; j > -1; j--) {
                if (pRecs[j]->Key > pR->Key)
                {
                    pRecs[j + 1] = pRecs[j];
                    Efficiency++;
                }
                else break;
            }
            pRecs[j + 1] = pR;
        }
    }
    void MergeSort(PTTabRecord* pMem, int DataCount) {
        PTTabRecord* pData = pRecs;
        PTTabRecord* pBuff = new PTTabRecord[DataCount];
        PTTabRecord* pTemp = pBuff;
        MergeSorter(pData, pBuff, DataCount);
        delete pTemp;
    }
    void MergeSorter(PTTabRecord*& pData, PTTabRecord*& pBuff, int size)
    {
        int n1 = (size + 1) / 2;
        int n2 = size - n1;
        if (size > 2)
        {
            PTTabRecord* pDat2 = pData + n1, * pBuff2 = pBuff + n1;
            MergeSorter(pData, pBuff, n1);
            MergeSorter(pDat2, pBuff2, n2);
        }
        MergeData(pData, pBuff, n1, n2);
    }

    void MergeData(PTTabRecord*& pData, PTTabRecord*& pBuff, int n1, int n2) {
        int i = 0, i1 = 0, i2 = 0;
        PTTabRecord* pDat1 = pData;
        PTTabRecord* pDat2 = pData + n1;
        while (i1 < n1 && i2 < n2) {
            if ((pDat1[i1]->Key) < (pDat2[i2]->Key))
                pBuff[i++] = pDat1[i1++];
            else
                pBuff[i++] = pDat2[i2++];
        }
        while (i1 < n1) pBuff[i++] = pDat1[i1++];
        while (i2 < n2) pBuff[i++] = pDat2[i2++];
        for (int j = 0; j < i; j++)
            pData[j] = pBuff[j];
        for (int j = 0; j < i; j++)
            pBuff[j] = pDat1[j];
        Efficiency += n1 + n2;
    }


    //
    void QuickSort(PTTabRecord* pMem, int DataCount)//
    {
        int pivot;
        int n1, n2;
        if (DataCount > 1)
        {
            QuickSplit(pMem, DataCount, pivot);
            n1 = pivot + 1;
            n2 = DataCount - n1;
            QuickSort(pMem, n1 - 1);
            QuickSort(pMem + n1, n2);
        }
    }

    void QuickSplit(PTTabRecord* pData, int size, int& pivot)//
    {
        PTTabRecord pPivot = pData[0], pTemp;
        int i1 = 1, i2 = size - 1;
        while (i1 <= i2)
        {
            while ((i1 < size) && !(pData[i1]->Key > pPivot->Key)) i1++;
            while (pData[i2]->Key > pPivot->Key) i2--;
            if (i1 < i2)
            {
                pTemp = pData[i1];
                pData[i1] = pData[i2];
                pData[i2] = pTemp;
            }
        }
        pData[0] = pData[i2];
        pData[i2] = pPivot;
        pivot = i2;
        Efficiency += size;
    }
    //
public:
    TSortTable(int Size = 20) : TScanTable(Size) {};
    TSortTable(const TScanTable& tab) {
        *this = tab;
        //        this->SortData();
    }

    TSortTable& operator=(const TScanTable& tab) {
        if (pRecs != nullptr)
        {
            for (int i = 0; i < DataCount; i++)
                delete pRecs[i];
            delete[] pRecs;
            pRecs = nullptr;
        }
        TabSize = tab.GetTabSize();
        DataCount = tab.GetDataCount();
        pRecs = new PTTabRecord[TabSize];
        for (int i = 0; i < DataCount; i++)
            pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
        SortData();
        CurPos = 0;
        return *this;
    }
    TSortMethod GetSortMethod(void) { return SortMethod; }
    void SetSortMethod(TSortMethod sm) { SortMethod = sm; }
    virtual PTDatValue FindRecord(TKey key) {
        int i, i1 = 0, i2 = DataCount - 1;
        Efficiency = 0;
        SetRetCode(TabOK);
        while (i1 <= i2)
        {
            Efficiency++;
            i = (i1 + i2) / 2;
            if (pRecs[i]->Key == key) {
                i1 = i + 1;
                i2 = i;
                break;
            }
            else if (pRecs[i]->Key > key)
                i2 = i - 1;
            else
                i1 = i + 1;
        }
        if (i2 < 0 || pRecs[i2]->GetKey() < key)
            i2++;
        CurPos = i2;
        if (i2 < DataCount&& pRecs[i2]->GetKey() == key) {
            SetRetCode(TabOK);
            return pRecs[i2]->GetValue();
        }
        SetRetCode(TabNoRecord);
        return nullptr;
    }
    virtual void InsRecord(TKey k, PTDatValue pVal) {
        if (IsFull()) {
            SetRetCode(TabFull);
        }
        else {
            PTDatValue temp = FindRecord(k);//
            if (temp != nullptr)
                SetRetCode(TabRecDbl);
            else {
                for (int i = DataCount; i > CurPos; i--)
                    pRecs[i] = pRecs[i - 1];
                pRecs[CurPos] = new TTabRecord(k, pVal);
                DataCount++;
                SetRetCode(TabOK);
            }
        }
    }

    virtual void DelRecord(TKey k) {

        PTDatValue temp = FindRecord(k);
        if (temp == nullptr)
            SetRetCode(TabNoRecord);
        else {
            for (int i = CurPos; i < DataCount - 1; i++)//--; i++)
                pRecs[i] = pRecs[i + 1];
            pRecs[--DataCount] = nullptr;
            SetRetCode(TabOK);
        }
    }

};