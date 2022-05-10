#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "TScanTable.h"
#include "ShoesTable.h"
class CSVConverter {
private:
    std::vector<std::pair<std::string, ShoesTable*>> Tab;
    std::ifstream File;
    std::string Path;
public:
    CSVConverter(std::string path) : Path(path) {}
    std::vector<std::pair<std::string, ShoesTable*>>& Convert() {
        char delim = ';';
        std::string buff;
        File.open(Path);
        if (File.is_open())
        {
            while (getline(File, buff))
            {
                size_t pos = 0;
                std::string model, color, tmp;
                int size, number;
                pos = buff.find(delim);
                model = buff.substr(0, pos);
                buff.erase(0, pos + 1);

                pos = buff.find(delim);
                color = buff.substr(0, pos);
                buff.erase(0, pos + 1);

                pos = buff.find(delim);
                size = stoi(buff.substr(0, pos));
                number = stoi(buff.substr(pos + 1));

                //     std::cout << std::endl << "mod=" << model << std::endl;
                ShoesTable* sh = new ShoesTable(color, size, number);
                std::pair<std::string, ShoesTable*> p;
                p = std::make_pair(model, sh);
                Tab.push_back(p);
            }
            File.close();
        }
        return Tab;
    };

};