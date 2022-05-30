#include "TScanTable.h"

PTDatValue TScanTable::FindRecord(TKey k)
{
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

void TScanTable::InsRecord(TKey k, PTDatValue pVal)
{
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

void TScanTable::DelRecord(TKey k)
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


std::ostream& operator<<(std::ostream& os, TScanTable& tab)
{

	tab.Reset();
	while (tab.GetCurPos() < tab.GetDataCount()) {
		os << tab.GetKey() << "   |" << tab.FindRecord(tab.GetKey())->ToString() << std::endl;
		tab.GoNext();
	}
	return os;
}
