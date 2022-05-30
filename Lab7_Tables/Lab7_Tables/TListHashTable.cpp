#include "TListHashTable.h"

TListHashTable::TListHashTable(int size = TabMaxSize) :THashTable()
{
	pList = new std::list<PTTabRecord>[size];
	TabSize = size;
	CurList = 0;
	for (int i = 0; i < TabSize; i++)
		pList[i] = std::list<PTTabRecord>();
}

TListHashTable::~TListHashTable()
{
	delete[] pList;
}

bool TListHashTable::IsFull() const
{
	return false;
}

PTDatValue TListHashTable::FindRecord(TKey k)
{
	Efficiency = 0;
	PTDatValue tmp = nullptr;
	CurList = HashFunc(k) % TabSize;
	std::list<PTTabRecord>* lst = pList + CurList;
	for (auto rec : *lst) {
		Efficiency++;
		if (rec->GetKey() == k) {
			tmp = rec->GetValue();
			break;
		}
	}
	return tmp;
}

void TListHashTable::InsRecord(TKey k, PTDatValue pVal)
{	
	PTDatValue temp = FindRecord(k);
	if (temp != nullptr)
		SetRetCode(TabRecDbl);
	else {
		CurList = HashFunc(k) % TabSize;
		std::list<PTTabRecord>* lst = pList + CurList;
		lst->push_back(new TTabRecord(k, pVal));
		SetRetCode(TabOK);
	}
}

void TListHashTable::DelRecord(TKey key)
{
	SetRetCode(TabOK);
	CurList = HashFunc(key) % TabSize;
	PTDatValue tmp = nullptr;
	for (auto rec : pList[CurList]) {
		Efficiency++;
		if (rec->GetKey() == key) {
			tmp = rec;
			break;
		}
	}
	if (tmp == nullptr) {
		SetRetCode(TabNoRecord);
		return;
	}
	pList[CurList].remove((PTTabRecord)tmp);
}

TKey TListHashTable::GetKey() const
{
	{return (*startChain)->GetKey(); }
}

PTDatValue TListHashTable::GetValue() const
{
	return (*startChain)->GetValue(); 
}

bool TListHashTable::Reset()
{
	CurList = 0;
	while (pList[CurList].size() == 0) {
		CurList++;
		if (IsTabEnded()) {
			return false;
		}
	}
	startChain = pList[CurList].begin();
	return !IsTabEnded();
}

bool TListHashTable::GoNext()
{
	startChain++;
	if (startChain != pList[CurList].end()) {
		return !IsTabEnded();
	}
	CurList++;
	while (pList[CurList].size() == 0 && !IsTabEnded())
	{
		CurList++;
	}
	if (IsTabEnded()) {
		return false;
	}

	startChain = pList[CurList].begin();
	return !IsTabEnded();

}

bool TListHashTable::IsTabEnded() const
{
	return CurList >= TabSize;
}

