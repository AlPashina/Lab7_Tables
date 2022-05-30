#include <iostream>
#include "TScanTable.h"
#include "TSortTable.h"
#include "ShoesRecord.h"
#include "CSVConverter.h"
#include "TListHashTable.h"

int main() {
	TListHashTable thash(25);
	TSortTable tsort(25);
	TSortTable tscan(25);

	std::cout << " *Insert record* " << std::endl << std::endl;
	std::string m = "smile";
	std::string co = "yellow";
	int s = 38, n = 2;
	ShoesRecord* g = new ShoesRecord(co, s, n);
	thash.InsRecord(m, g);
	tscan.InsRecord(m, g);
	
	std::cout << " *Getting table form the file* " << std::endl << std::endl;
	std::vector<std::pair<std::string, ShoesRecord*>> res;
	CSVConverter* c = new CSVConverter("../Shoes1.csv");
	res = c->Convert();
	for (int i = 0; i < res.size(); i++) {
		thash.InsRecord(res[i].first, res[i].second);
	tscan.InsRecord(res[i].first, res[i].second);
	}
	tsort = tscan;


	std::cout << "Hash Table" << std::endl;
	std::cout << " Model" << "  |   " << "Color" << "  |   " << "Size" << "  |   " << "Number" << std::endl;
	std::cout  << "-------------------------------------------" << std::endl;
	std::cout << thash << std::endl;
	std::cout << "Sort Table" << std::endl;
	std::cout << " Model" << "  |   " << "Color" << "  |   " << "Size" << "  |   " << "Number" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << tsort << std::endl;

	std::cout << std::endl << " *Finding record by key 'start'* " << std::endl << std::endl;
	std::cout<< (thash.FindRecord("start"))->ToString()<<std::endl;
	std::cout << thash.GetEfficiency() << std::endl;
	std::cout << (tsort.FindRecord("start"))->ToString() << std::endl;
	std::cout << tsort.GetEfficiency() << std::endl;

	std::cout << std::endl << " *Deleting record by key 'start'* " << std::endl << std::endl;
	thash.DelRecord("start");
	tsort.DelRecord("start");

	
	std::cout << "Hash Table" << std::endl;
	std::cout << " Model" << "  |   " << "Color" << "  |   " << "Size" << "  |   " << "Number" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << thash << std::endl;
	std::cout << "Sort Table" << std::endl;
	std::cout << " Model" << "  |   " << "Color" << "  |   " << "Size" << "  |   " << "Number" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << tsort << std::endl;


	return 0;
}