#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int digitToInt(const char ch) { return ch - '0'; }

bool isLowPoint(vector<string>& heightmap, size_t x, size_t y) {
	int cellValue = digitToInt(heightmap[y][x]);

	if (y != heightmap.size()-1    && cellValue >= digitToInt(heightmap[y+1][x])) return false;
	if (y != 0                     && cellValue >= digitToInt(heightmap[y-1][x])) return false;
	if (x != heightmap[0].size()-1 && cellValue >= digitToInt(heightmap[y][x+1])) return false;
	if (x != 0                     && cellValue >= digitToInt(heightmap[y][x-1])) return false;

	return true;
}

int main(int argc, char* argv[]) {
	vector<string> heightmap;

	{
		ifstream ifs("09\\input.txt");
		string line;
		while (getline(ifs, line)) {
			heightmap.push_back(line);
		}
	}

	size_t total = 0;
	for (size_t y = 0; y < heightmap.size(); y++) {
		for (size_t x = 0; x < heightmap[0].size(); x++) {
			if (isLowPoint(heightmap, x, y)) {
				total += 1 + digitToInt(heightmap[y][x]);
			}
		}
	}

	cout << "Risk level of low points: " << total << endl;
}