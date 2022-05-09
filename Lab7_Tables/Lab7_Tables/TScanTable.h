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

	//}
	//virtual void  DelRecord(const TKey k) override {
	//	auto record = FindRecord(k);
	//	if (record == nullptr) {
	//		SetRetCode(TabNoRecord); //return
	//		return;//
	//	}

	//	SetRetCode(TabOK);
	//	pRecs[CurPos] = dynamic_cast<PTTabRecord>(pRecs[DataCount - 1]->GetCopy());
	//	delete pRecs[DataCount - 1];
	//	delete record;
	//	DataCount--;
	//	SetRetCode(TabOK);//return TabOK;

	//	//or 
	//	if (IsEmpty())
	//		return;
	//	for (int i = 0; i < DataCount; ++i) {
	//		++Efficiency;
	//		if (!pRecs[i])
	//			continue;
	//		if (pRecs[i]->Key == k) {
	//			delete pRecs[i];
	//			for (int j = i + 1; j < DataCount; ++j)
	//				pRecs[j - 1] = pRecs[j];
	//			--DataCount;
	//			break;
	//		}
	//	}

	//}

	
	virtual void InsRecord (TKey k, PTDatValue pVal ) { //efficiency?
		SetRetCode(TabOK);
		if (IsFull()) {
			SetRetCode(TabFull);
			return;
		}

		this->FindRecord(k);
		if (GetRetCode()==TabOK) {
			return;
		}
		SetRetCode(TabOK);
		this->pRecs[this->CurPos++] = new TTabRecord(k, pVal);
		this->DataCount++;
	}


	virtual void  DelRecord(TKey k) {
		SetRetCode(TabOK);
		if (IsEmpty()) {
			SetRetCode(TabEmpty);
			return;
		}
		for (int i = 0; i < GetDataCount(); i++)
			if (pRecs[i]->GetKey() == k)
			{
				delete pRecs[i]->pValue;//
				delete pRecs[i]; 
				pRecs[i] = nullptr;
				pRecs[i] = pRecs[DataCount - 1];
				pRecs[DataCount - 1] = nullptr;
				Efficiency = i + 1;
				DataCount--;
				return;
			}
		Efficiency++;
	}
	
};