#include <iostream>
#include "TScanTable.h"
#include "ShoesTable.h"
#include "CSVConverter.h"

int main() {
	TScanTable* t = new TScanTable();
	std::cout << " *Insert record* " << std::endl << std::endl;
	std::string m = "cool!";
	std::string co = "brown";
	int s = 40, n = 2;
	ShoesTable* g = new ShoesTable(co, s, n);
	t->InsRecord(m, g);
	std::cout << " Model" << "  |   " << "Color" << "  |   " << "Size" << "  |   " << "Number";
	std::cout << *t << std::endl;
	std::cout << " *Getting table form the file* " << std::endl << std::endl;
	std::vector<std::pair<std::string, ShoesTable*>> res;
	CSVConverter* c = new CSVConverter("../Shoes2.csv");
	res = c->Convert();
	for (int i = 0; i < res.size(); i++) {
		t->InsRecord(res[i].first, res[i].second);
	}
	std::cout << " Model" << "  |   " << "Color" << "  |   " << "Size" << "  |   " << "Number";
	std::cout << *t << std::endl;
	std::cout << std::endl << " *Finding record by key* " << std::endl << std::endl;
	std::cout << "Key=start  " << t->FindRecord("start")->ToString() << std::endl;
	std::cout << std::endl << " *Deleting record by key* " << std::endl << std::endl;
	t->DelRecord("start");
	std::cout << " Model" << "  |   " << "Color" << "  |   " << "Size" << "  |   " << "Number";
	std::cout << *t << std::endl;
	return 0;
}