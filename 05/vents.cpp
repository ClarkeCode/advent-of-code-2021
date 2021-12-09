
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

void addCoordinates(std::map<std::string, size_t>& coordinates, std::string line) {
	using namespace std;
	size_t x1, y1, x2, y2;
	
	{
		string s1 = line.substr(0, line.find(" -> "));
		string s2(line.begin() + line.rfind(" -> ")+4, line.end());
		// cout << "'" << s1 << "'" << "'" << s2 << "'" << endl;

		stringstream ss1(s1);
		stringstream ss2(s2);
		char discard;
		ss1 >> x1 >> discard >> y1;
		ss2 >> x2 >> discard >> y2;
		if (x1 != x2 && y1 != y2) return; //Ignore non-orthogonal lines
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
	}

	bool xVariant = x1 != x2;

	for (size_t change = (xVariant ? x1 : y1); change <= (xVariant ? x2 : y2); change++) {
		string key;

		{
			char buff[32] = "";
			sprintf(buff, "%lu,%lu", (xVariant ? change : x1), (xVariant ? y1 : change));
			key = string(buff);
		}

		coordinates[key]++;
	}
}

int main(int argc, char* argv[]) {
	using namespace std;

	ifstream ifs("05\\input.txt");	

	map<string, size_t> coordinates;

	string line;
	while (getline(ifs, line)) {
		// printf("%s\n", line.c_str());
		addCoordinates(coordinates, line);
	}

	size_t acc = 0;
	for (auto x : coordinates) {
		if (x.second >= 2) { acc++; }
	}
	cout << "Overlapping points: " << acc << endl;
}