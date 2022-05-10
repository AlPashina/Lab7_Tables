#pragma once
#include "TArrayTable.h"

class TScanTable :public TArrayTable {
public:
	TScanTable(int size = 25) :TArrayTable(size) { }
	virtual PTDatValue FindRecord(TKey k) {
		SetRetCode(TabOK);
		int i;
		for (i = 0; i < DataCount; i++) {
			if (pRecs[i]->Key == k)
				break;
		}
		Efficiency = i + 1;
		if (i < DataCount)
		{
			CurPos = i;
			return pRecs[i]->pValue;
		}
		SetRetCode(TabNoRecord);
		return nullptr;
	}
	virtual void InsRecord(TKey k, PTDatValue pVal) {
		SetRetCode(TabOK);
		if (this->IsFull()) {
			SetRetCode(TabFull);
			return;
		}
		this->FindRecord(k);
		if (this->GetRetCode() == TabOK) {
			return;
		}
		SetRetCode(TabOK);
		this->pRecs[this->CurPos++] = new TTabRecord(k, pVal);
		this->DataCount++;

	}

	virtual void  DelRecord(TKey k)
	{
		if (!IsEmpty())
		{
			if (FindRecord(k) == nullptr)
				SetRetCode(TabNoRecord);
			else
			{
				delete pRecs[CurPos];
				pRecs[CurPos] = nullptr;
				pRecs[CurPos] = pRecs[DataCount - 1];
				pRecs[DataCount - 1] = nullptr;
				DataCount--;
				SetRetCode(TabOK);
			}
		}
		else
			SetRetCode(TabEmpty);
	}

	//virtual void  DelRecord(TKey k) {
	//	SetRetCode(TabOK);
	//	if (IsEmpty()) {
	//		SetRetCode(TabEmpty);
	//		return;
	//	}
	//	for (int i = 0; i < GetDataCount(); i++)
	//		if (pRecs[i]->GetKey() == k)
	//		{
	//			//delete pRecs[i]->pValue;
	//			delete pRecs[i];
	//			pRecs[i] = nullptr;
	//			pRecs[i] = pRecs[DataCount - 1];
	//			pRecs[DataCount - 1] = nullptr;
	//			Efficiency = i + 1;
	//			DataCount--;
	//			return;
	//		}
	//	Efficiency++;
	//}

	friend std::ostream& operator<<(std::ostream& os, TScanTable& tab)
	{

		os << std::endl << "-------------------------------------------" << std::endl;
		tab.Reset();
		while (tab.GetCurPos() < tab.GetDataCount()) {
			os << tab.GetKey() << "   |" << tab.FindRecord(tab.GetKey())->ToString() << std::endl;
			tab.GoNext();
		}
		return os;
	}
};
