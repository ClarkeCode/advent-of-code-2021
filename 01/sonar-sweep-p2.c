#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SZ 256

void shiftValuesLeft(int* values) {
	for (size_t x = 0; x < 3; x++) {
		*(values+x) = *(values+x+1);
	}
}

int procureValue(FILE* fp, int* newValue) {
	char buff[BUFF_SZ] = {0};
	if (!fgets(buff, BUFF_SZ, fp)) { return EOF; }
	*newValue = atoi(buff);
	return 1;
}

int main (int argc, char* argv[]) {
	FILE* fp = fopen("01\\input.txt", "r");
	if (!fp) fprintf(stderr, "ERROR: Cannot open input file\n");

	size_t num_depth_increases = 0;
	int measurements[4] = {0};

	for (size_t x = 0; x < 3; x++) {
		if (procureValue(fp, measurements+x) == EOF) fprintf(stderr, "ERROR: Cannot fill initial measurements\n");
	}

	while (procureValue(fp, measurements+3) != EOF) {
		int partialSum = *(measurements+1) + *(measurements+2);
		int prevSum = *measurements + partialSum;
		int currSum = *(measurements+3) + partialSum;
		if (currSum > prevSum) {
			num_depth_increases++;
		}
		shiftValuesLeft(measurements);
	}
	fclose(fp);

	fprintf(stdout, "The depth measurement increases %lu times\n", num_depth_increases);
}