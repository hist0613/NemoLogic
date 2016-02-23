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
		nl.input(ifstream("input" + to_string(ti) + ".txt"));
		nl.solve(0, false);
		// nl.output(cout);
		nl.output(ofstream("output" + to_string(ti) + ".txt"));
	}
	return 0;
}