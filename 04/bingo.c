#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
	int numbers[5];
	bool chosen[5];
} BingoRow;

char fpeek(FILE* fp) {
	char c = getc(fp);
	ungetc(c, fp);
	return c;
}
void discardchars(FILE* fp, char c) {
	while (fpeek(fp) == c) { getc(fp); }
}

int readNumber(FILE* fp, char terminator, bool ungetNewlines) {
	char buff[64] = {0};
	char c;
	while ((c=getc(fp)) != EOF && c != terminator && c != '\n') {
		buff[strlen(buff)] = c;
	}
	if (c == '\n' && ungetNewlines) ungetc(c, fp);
	return atoi(buff);
}

void loadCallNumgers(FILE* fp, int** meta, size_t* arr_sz) {
	while (fpeek(fp) != '\n') {
		int val = readNumber(fp, ',', true);
		int* arr = *meta;
		arr = realloc(arr, sizeof(int) * (*arr_sz + 1));
		*(arr + (*arr_sz)++) = val;
		*meta = arr;
	}
}

void loadBingoRow(FILE* fp, BingoRow* br, int* vals) {
	for (size_t x = 0; x < 5; x++) {
		br->numbers[x] = *(vals+x);
	}
}

bool isBoardSolved(bool* chosen) {
	for (size_t x = 0; x < 5; x++) {
		if (*(chosen+x+0) && *(chosen+x+1) && *(chosen+x+2) && *(chosen+x+3) && *(chosen+x+4))
			return true; //Horizontal row
		if (*(chosen+(5*x)+0) && *(chosen+(5*x)+1) && *(chosen+(5*x)+2) && *(chosen+(5*x)+3) && *(chosen+(5*x)+4))
			return true; //Vertical Row
	}
	return false;
}

void callNumber(int* board, bool* chosen, int called) {
	for (size_t x = 0; x < 25; x++) {
		if (*(board+x) == called) *(chosen+x) = true;
	}
}

int uncalledSum(int* board, bool* chosen) {
	int sum = 0;
	for (size_t x = 0; x < 25; x++) {
		if (! *(chosen+x)) sum += *(board+x);
	}
	return sum;
}

void readBingoBoard(FILE* fp, int* call_nums, size_t call_sz, bool* gotBingo, size_t*bingoOn, int* winningNum, int* sum) {
	int boardNums[25] = {0};
	bool chosen[25] = {0};
	int temp[5] = {0};
	discardchars(fp, '\n');
	for (size_t x = 0; x < 25; x++) {
		discardchars(fp, ' ');
		boardNums[x] = readNumber(fp, ' ', false);
	}

	for (size_t x = 0; x < call_sz; x++) {
		callNumber(boardNums, chosen, *(call_nums+x));
		if (isBoardSolved(chosen)) {
			*gotBingo = true;
			*bingoOn = x;
			*winningNum = *(call_nums+x);
			*sum = uncalledSum(boardNums, chosen);
		}
	}


	discardchars(fp, '\n');
}

int main (int argc, char* argv[]) {
	FILE* fp = fopen("04\\sample.txt", "r");
	if (!fp) fprintf(stderr, "ERROR: Cannot open file\n");

	int* callNum = malloc(sizeof(int));
	size_t call_sz = 0;
	loadCallNumgers(fp, &callNum, &call_sz);

	for (size_t x = 0; x < call_sz; x++) {
		fprintf(stdout, "%d ", *(callNum + x));
	}

	size_t quickest = -1;
	int product = 0;

	bool hasBingo = false;
	size_t bingoOn = -1;
	int win = 0;
	int sum = 0;
	while (fpeek(fp) != EOF) {
		readBingoBoard(fp, callNum, call_sz, &hasBingo, &bingoOn, &win, &sum);
		if (hasBingo && bingoOn < quickest) {
			product = win*sum;
			hasBingo = false;
		}
	}

	fprintf(stdout, "Product: %lu\n", product);

	fclose(fp);
}