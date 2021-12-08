#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

using atlas_t = map<string, size_t>;


int main (int argc, char* argv[]) {
	size_t occurances = 0;

	{
		ifstream ifs("08\\input.txt");
		string line;
		while (getline(ifs, line)) {
			string val;
			stringstream ss(line);
			ss.ignore(2048, '|');
			while (ss >> val) {
				if (val.size() == 2 || val.size() == 3 || val.size() == 4 || val.size() == 7)
					occurances++;
			}
		}
	}

	cout << occurances << endl;
}