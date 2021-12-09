#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void loadCallNum(vector<size_t>& callNums, string line) {
	stringstream ss(line);
	size_t val;
	char discard;

	while (ss >> val) {
		ss >> discard;
		callNums.push_back(val);
	}
}

using square_t = pair<size_t, bool>;
using board_t = vector<square_t>;

void callNumOnBoard(board_t& board, size_t num) {
	for (square_t& square : board) {
		if (square.first == num) {
			square.second = true;
			break;
		}
	}
}

bool boardHasBingo(board_t& board) {
	//Test horizontals
	for (size_t x = 0; x < 5; x++) {
		if (board[5*x+0].second &&
			board[5*x+1].second &&
			board[5*x+2].second &&
			board[5*x+3].second &&
			board[5*x+4].second) {
			return true;
		}
	}

	//Test verticals
	for (size_t y = 0; y < 5; y++) {
		if (board[5*0+y].second &&
			board[5*1+y].second &&
			board[5*2+y].second &&
			board[5*3+y].second &&
			board[5*4+y].second) {
			return true;
		}
	}

	return false;
}

size_t getBoardScore(board_t& board, size_t lastNum) {
	size_t score = 0;
	for (square_t& square : board) {
		if (!square.second) score += square.first;
	}
	return score * lastNum;
}

bool testBingoBoard(ifstream& ifs, vector<size_t>& callNums, size_t& boardScore, size_t& bingoAfter) {
	bool hasBingo = false;
	size_t score = 0;

	board_t board;

	size_t val;
	for (size_t x = 0; x < 25; x++) {
		ifs >> val;
		board.push_back(square_t(val, false));
	}

	size_t calls = 0;
	for (size_t& num : callNums) {
		calls++;
		callNumOnBoard(board, num);
		if (hasBingo = boardHasBingo(board)) {
			score = getBoardScore(board, num);
			break;
		}
	}

	bingoAfter = calls;
	if (hasBingo) boardScore = score;
	return hasBingo;
}

int main(int argc, char* argv[]) {
	vector<size_t> callNums;

	size_t bestScore;
	size_t latestBingo = 0;
	{
		ifstream ifs("04\\input.txt");
		string line;
		getline(ifs, line);
		loadCallNum(callNums, line);
		
		while (ifs.peek() != EOF) {
			
			size_t score, after;
			testBingoBoard(ifs, callNums, score, after);

			if (after > latestBingo) {
				bestScore = score;
				latestBingo = after;
			}
		}
	}

	cout << "Last bingo is after " << latestBingo << " numbers, with score of " << bestScore << endl;
}