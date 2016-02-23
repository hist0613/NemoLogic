#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "NemoLogic.h"

int main(void) {
	for (int ti = 1; ti <= 7; ti++) {
		NemoLogic nl;
		ifstream fin("input" + to_string(ti) + ".txt");
		ofstream fout("output" + to_string(ti) + ".txt");
		nl.input(fin);
		nl.solve(0, false);
		// nl.output(cout);
		nl.output(fout);
	}
	return 0;
}
