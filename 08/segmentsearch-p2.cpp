#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;


using atlas_t = map<string, size_t>;

// template<typename key_t, typename val_t>
// vector<key_t> getKeys(map<key_t, val_t> const& m) {
// 	vector<key_t> output;
// 	for (auto& pair : m) output.push_back(pair.first);
// 	return output;
// }

string sortedString(stringstream& ss) {
	string str;
	ss >> str;
	sort(str.begin(), str.end());
	return str;
}

bool hasAllLetters(string const& test, string const& compare, char* missing = nullptr) {
	for (const char& ch : compare) {
		if (test.find(ch, 0) == string::npos) {
			if (missing) *missing = ch;
			return false;
		}
	}
	return true;
}

void populateAtlas(stringstream&ss, atlas_t& atlas) {
	for (size_t x = 0; x < 10; x++) {
		atlas[sortedString(ss)] = -1;
	}

	string key7;
	string key4;
	char segC;
	string segC_s = " ";

	vector<atlas_t::key_type> sixLenKeys;
	vector<atlas_t::key_type> fiveLenKeys;

	//unique length -> #1, #7, #4, #8
	for (auto& pair : atlas) {
		if (pair.first.length() == 2) pair.second = 1;
		if (pair.first.length() == 3) {pair.second = 7; key7 = pair.first;}
		if (pair.first.length() == 4) {pair.second = 4; key4 = pair.first;}
		if (pair.first.length() == 7) pair.second = 8;
		if (pair.first.length() == 6) sixLenKeys.push_back(pair.first);
		if (pair.first.length() == 5) fiveLenKeys.push_back(pair.first);
	}

	//6 len
	//if missing seg of #7 -> #6 (extract seg c)
	//-if missing seg of #4 -> #0
	//-then -> #9
	for (auto it = sixLenKeys.begin(); it != sixLenKeys.end(); it++) {
		if (!hasAllLetters(*it, key7, &segC)) {
			segC_s[0] = segC;
			atlas[*it] = 6;
			sixLenKeys.erase(it);
			break;
		}
	}
	if (!hasAllLetters(sixLenKeys[0], key4)) {
		atlas[sixLenKeys[0]] = 0;
		atlas[sixLenKeys[1]] = 9;
	}
	else {
		atlas[sixLenKeys[0]] = 9;
		atlas[sixLenKeys[1]] = 0;
	}

	//5 len
	//if has all seg of #7 -> #3
	//-if has seg 'c' -> #2
	//-remaining -> #5
	auto it = fiveLenKeys.begin();
	for (; it != fiveLenKeys.end(); it++) {
		if (hasAllLetters(*it, key7)) {
			atlas[*it] = 3;
			fiveLenKeys.erase(it);
			break;
		}
	}

	if (hasAllLetters(fiveLenKeys[0], segC_s)) {
		atlas[fiveLenKeys[0]] = 2;
		atlas[fiveLenKeys[1]] = 5;
	}
	else {
		atlas[fiveLenKeys[0]] = 5;
		atlas[fiveLenKeys[1]] = 2;
	}
}

size_t decodeValue(stringstream& ss) {
	atlas_t atlas;
	populateAtlas(ss, atlas);

	ss.ignore(2048, '|');
	size_t value = 0;
	for (size_t x = 0; x < 4; x++) {
		value *= 10;
		value += atlas[sortedString(ss)];
	}


	return value;
}

int main (int argc, char* argv[]) {
	size_t total = 0;

	{
		ifstream ifs("08\\input.txt");
		string line;
		while (getline(ifs, line)) {
			total += decodeValue(stringstream(line));
		}
	}

	cout << total << endl;
}