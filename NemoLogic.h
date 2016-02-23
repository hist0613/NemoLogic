#ifndef NEMOLOGIC_H
#define NEMOLOGIC_H

#include <iostream>
#include <vector>
using namespace std;

class NemoLogic {
public:
	bool solve(int ri, bool debug = false);
	bool check_col(int ci);
	void input(istream &input);
	void output(ostream &output);

private:
	int row_size, col_size;
	vector< vector<int> > row_hints;
	vector< vector<int> > col_hints;
	vector< vector<int> > board;
};

int sum(vector<int> &vi);

#endif NEMOLOGIC_H