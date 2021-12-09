#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

using coord_t = pair<size_t, size_t>;

int digitToInt(const char ch) { return ch - '0'; }

bool isLowPoint(vector<string>& heightmap, size_t x, size_t y) {
	int cellValue = digitToInt(heightmap[y][x]);

	if (y != heightmap.size()-1    && cellValue >= digitToInt(heightmap[y+1][x])) return false;
	if (y != 0                     && cellValue >= digitToInt(heightmap[y-1][x])) return false;
	if (x != heightmap[0].size()-1 && cellValue >= digitToInt(heightmap[y][x+1])) return false;
	if (x != 0                     && cellValue >= digitToInt(heightmap[y][x-1])) return false;

	return true;
}

//Implemented floodfill algorithm described at https://en.wikipedia.org/wiki/Flood_fill#Moving_the_recursion_into_a_data_structure
size_t sizeOfBasin(vector<string>& heightmap, coord_t& lowPoint, coord_t& maxVal) {
	stack<coord_t> testLocations;
	testLocations.push(lowPoint);
	vector<coord_t> alreadyTested;

	size_t basinSize = 0;
	while (!testLocations.empty()) {
		coord_t coord = testLocations.top();
		testLocations.pop();
		

		if (heightmap[coord.second][coord.first] != '9' && find(alreadyTested.begin(), alreadyTested.end(), coord) == alreadyTested.end()) {
			alreadyTested.push_back(coord);
			basinSize++;
			if (coord.first != 0)              testLocations.push(coord_t(coord.first-1, coord.second));
			if (coord.first != maxVal.first)   testLocations.push(coord_t(coord.first+1, coord.second));
			if (coord.second != 0)             testLocations.push(coord_t(coord.first, coord.second-1));
			if (coord.second != maxVal.second) testLocations.push(coord_t(coord.first, coord.second+1));
		}
	}

	return basinSize;
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

	vector<size_t> basinSizes;
	for (size_t y = 0; y < heightmap.size(); y++) {
		for (size_t x = 0; x < heightmap[0].size(); x++) {
			if (isLowPoint(heightmap, x, y)) {
				basinSizes.push_back(sizeOfBasin(heightmap, coord_t(x,y), coord_t(heightmap[0].size()-1, heightmap.size()-1)));
			}
		}
	}

	sort(basinSizes.begin(), basinSizes.end());
	reverse(basinSizes.begin(), basinSizes.end());

	cout << "Product of 3 largest basins: " << basinSizes[0]*basinSizes[1]*basinSizes[2] << endl;
}