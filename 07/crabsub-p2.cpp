#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

using subs_t = vector<size_t>;

size_t fuelCost(size_t distance) {
	static vector<size_t> sequence = {0, 1};
	while (sequence.size() <= distance) {
		sequence.push_back(*sequence.rbegin() + (sequence.end() - sequence.begin()));
	}

	return sequence[distance];
}

size_t alignmentCost(subs_t& container, size_t index) {
	size_t fuelcost = 0;
	auto alignment = container.begin()+index;

	for (auto& it = container.begin(); it != container.end(); ++it) {
		if (it == alignment) continue;
		if (it < alignment) {
			fuelcost += *it * fuelCost(alignment-it);
		}
		else {
			fuelcost += *it * fuelCost(it-alignment);
		}
	}
	return fuelcost;
}

int main(int argc, char* argv[]) {
	subs_t state;

	{
		ifstream ifs("07\\input.txt");
		string line;
		while (getline(ifs, line)) {
			size_t val;
			stringstream ss(line);
			while (ss >> val) {
				while (val >= state.size()) {
					state.push_back(0);
				}
				state[val]++;
				ss.get();
			}
		}
	}

	size_t bestCost = -1;
	size_t bestIndex = 0;
	for (size_t x = 0; x < state.size(); x++) {
		size_t cost = alignmentCost(state, x);
		if (cost < bestCost) {
			bestCost = cost;
			bestIndex = x;
		}
	}
	cout << "Lowest cost " << bestCost << " at " << bestIndex << endl;

}