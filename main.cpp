#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class NemoLogic {
public:
	NemoLogic();
	~NemoLogic();
	bool solve();
	int check_row(int ri);
	int check_col(int ci);
private:
	int row_size, col_size;
	vector< vector<int> > row_hints;
	vector< vector<int> > col_hints;
	vector< vector<int> > board;
};

bool NemoLogic::solve(){
	vector<int> row_check(row_size, 0);
	vector<int> col_check(col_size, 0);
	while (true){
		int checked = 0;
		for (int ri = 0; ri < row_size; ri++) row_check[ri] = check_row(ri);
		for (int ci = 0; ci < col_size; ci++) col_check[ci] = check_col(ci);
	}
}

int main(void){
	return 0;
}