#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "NemoLogic.h"

void NemoLogic::input(istream &input){
    input >> row_size >> col_size;
    
    row_hints.resize(row_size, vector<int>());
    for (int ri = 0; ri < row_size; ri++){
        string line;
        getline(input, line);

        stringstream ss(line); int temp;
        while (ss >> temp) row_hints[ri].push_back(temp);
    }

    col_hints.resize(col_size, vector<int>());
    for (int ci = 0; ci < col_size; ci++){
        string line;
        getline(input, line);

        stringstream ss(line); int temp;
        while (ss >> temp) col_hints[ci].push_back(temp);
    }
}