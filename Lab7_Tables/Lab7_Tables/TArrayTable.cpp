
#include "TArrayTable.h"
TArrayTable::TArrayTable(int size) :TabSize(size)
{
	pRecs = new PTTabRecord[TabSize];
	for (int i = 0; i < TabSize; i++) {
		pRecs[i] = 0;
	}
	CurPos = 0;
};
TArrayTable::~TArrayTable()
{
	for (int i = 0; i < TabSize; i++) {
		delete pRecs[i];
	}
	delete[]pRecs;
}

bool TArrayTable::IsFull() const
{
	return DataCount >= TabSize;
}

int TArrayTable::GetTabSize() const
{
	return TabSize;
}

PTDatValue TArrayTable::GetValue() const
{
	return GetValue(CURRENT_POS);
}

TKey TArrayTable::GetKey() const
{
	return GetKey(CURRENT_POS);
}

TKey TArrayTable::GetKey(TDataPos mode) const
{
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

PTDatValue TArrayTable::GetValue(TDataPos mode) const
{
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

bool TArrayTable::Reset()
{
	CurPos = 0;
	return IsTabEnded();
}

bool TArrayTable::IsTabEnded() const
{
	return CurPos >= TabSize;
}

bool TArrayTable::GoNext()
{
	if (!IsTabEnded())
		CurPos++;
	return IsTabEnded();
}

int TArrayTable::GetCurPos() const
{
	return CurPos;
}

bool TArrayTable::SetCurPos(int pos)
{
	CurPos = ((pos > -1) && (pos < DataCount)) ? pos : 0;
	return IsTabEnded();
}