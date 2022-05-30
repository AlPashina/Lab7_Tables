#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "TScanTable.h"
#include "ShoesRecord.h"
class CSVConverter {
private:
    std::vector<std::pair<std::string, ShoesRecord*>> Tab;
    std::ifstream File;
    std::string Path;
public:
    CSVConverter(std::string path) : Path(path) {}
    std::vector<std::pair<std::string, ShoesRecord*>>& Convert() {
        char semicolon = ';';
        std::string buff;
        File.open(Path);
        if (File.is_open())
        {
            while (getline(File, buff))
            {
                size_t pos = 0;
                std::string model, color, tmp;
                int size, number;
                pos = buff.find(semicolon);
                model = buff.substr(0, pos);
                buff.erase(0, pos + 1);
                pos = buff.find(semicolon);
                color = buff.substr(0, pos);
                buff.erase(0, pos + 1);
                pos = buff.find(semicolon);
                size = stoi(buff.substr(0, pos));
                number = stoi(buff.substr(pos + 1));
                ShoesRecord* sh = new ShoesRecord(color, size, number);
                std::pair<std::string, ShoesRecord*> p;
                p = std::make_pair(model, sh);
                Tab.push_back(p);
            }
            File.close();
        }
        return Tab;
    };

};