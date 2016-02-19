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
    input.ignore(1);

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

    board.resize(row_size, vector,int>(col_size));
}

void NemoLogic::output(ostream &output){
    int margin_left = 0, max_cnt_row_hints = 0, left_max_digits = 0;
    int margin_top = 0, max_cnt_col_hints = 0, top_max_digits = 0;

    for (int ri = 0; ri < row_size; ri++){
        max_cnt_row_hints = max((int)row_hints[ri].size(), max_cnt_row_hints);
        for (int hi = 0; hi < row_hints[ri].size(); hi++){
            left_max_digits = max((int)to_string(row_hints[ri][hi]).size(), left_max_digits);
        }
    }
    for (int ci = 0; ci < col_size; ci++){
        max_cnt_col_hints = max((int)col_hints[ci].size(), max_cnt_col_hints);
        for (int hi = 0; hi < col_hints[ci].size(); hi++){
            top_max_digits = max((int)to_string(col_hints[ci][hi]).size(), top_max_digits);
        }
    }

    margin_left = (left_max_digits + 1) * max_cnt_row_hints;
    margin_top = top_max_digits * max_cnt_col_hints;

    // print col_hints
    for (int hi = 0; hi < max_cnt_col_hints; hi++){
        cout << setw(margin_left) << ' ';
        for (int ci = 0; ci < col_size; ci++){
            cout << setw(top_max_digits + 1);
            if (hi >= max_cnt_col_hints - col_hints[ci].size()){
                cout << col_hints[ci][hi - max_cnt_col_hints + col_hints[ci].size()];
            }
            else{
                cout << ' ';
            }
        }
        cout << endl;
    }

    for (int ri = 0; ri < row_size; ri++){
        // print row hints
        for (int hi = 0; hi < max_cnt_row_hints; hi++){
            cout << setw(left_max_digits + 1);
            if (hi >= max_cnt_row_hints - row_hints[ri].size()){
                cout << row_hints[ri][hi - max_cnt_row_hints + row_hints[ri].size()];
            }
            else{
                cout << ' ';
            }
        }

        // print board
        for (int ci = 0; ci < col_size; ci++){
            cout << setw(top_max_digits + 1);
            if (board[ri][ci] == 1) cout << "■";
            else if (board[ri][ci] == -1) cout << 'X';
            else cout << "□";
        }

        cout << endl;
    }
}