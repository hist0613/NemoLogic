#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "NemoLogic.h"

int main(void){
	for (int ti = 0; ti < 5; ti++){
		NemoLogic nl;
		nl.input(ifstream("input" + to_string(ti) + ".txt"));
		nl.solve();
		nl.output(cout);
	}
	return 0;
}