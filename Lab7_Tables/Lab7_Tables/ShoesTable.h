#pragma once

#include "TDatValue.h"
class ShoesTable :public TDatValue
{
protected:
	std::string Color;
	int Size;
	int Number;
public:

	ShoesTable(std::string color, int size, int num) {
		Color = color;
		Size = size;
		Number = num;
	}


	std::string GetColor() {
		return Color;
	}
	int GetSize() {
		return Size;
	}
	int GetNumber() {
		return Number;
	}

	TDatValue* GetCopy() {
		return new ShoesTable(Color, Size, Number);
	}


	std::string ToString() {
		std::string res = "   " + Color + "  |   " + std::to_string(Size) + "    |   " + std::to_string(Number);
		return res;
	}
	friend std::ostream& operator<<(std::ostream& os, ShoesTable& tab)
	{
		os << tab.GetColor() << "     "
			<< tab.GetSize() << "     "
			<< tab.GetNumber() << "     ";

		return os;
	}

};
