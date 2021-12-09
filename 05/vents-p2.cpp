
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
std::string getCoordStr(size_t x, size_t y) {
	char buff[32] = "";
	sprintf(buff, "%lu,%lu", x, y);
	return std::string(buff);
}

void incrementTowards(size_t& a, size_t const& b) {
	if (a == b)     return;
	else if (a > b) a--;
	else            a++;
}

void addCoordinates(std::map<std::string, size_t>& coordinates, std::string& line) {
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
	}

	while (!(x1 == x2 && y1 == y2)) {
		string key = getCoordStr(x1, y1);
		coordinates[key]++;

		incrementTowards(x1, x2);
		incrementTowards(y1, y2);
	}
	coordinates[getCoordStr(x1, y1)]++;

}

void displayBoard(std::map<std::string, size_t>& coordinates) {
	using namespace std;
	for (size_t y = 0; y < 10; y++) {
		for (size_t x = 0; x < 10; x++) {
			size_t val = coordinates[getCoordStr(x, y)];
			if (val == 0) cout << '.';
			else cout << val;
		}
		cout << endl;
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
		// displayBoard(coordinates);
		// cout << endl;
	}

	size_t acc = 0;
	for (auto x : coordinates) {
		if (x.second >= 2) { acc++; }
	}

	

	cout << "Overlapping points: " << acc << endl;
}