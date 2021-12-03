#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFF_SZ 128

void incrementCounts(char* buff, int* ones, int* zeros) {
	char* current = buff;
	size_t offset = 0;
	while (current && *current != '\0') {
		if (*current == '1') *(ones+offset) += 1;
		if (*current == '0') *(zeros+offset) += 1;
		offset++;
		current++;
	}
}

size_t determineRate(size_t data_width, int* ones, int* zeros, bool getGamma) {
	size_t temp = 0;
	for (size_t x = 0; x < data_width; x++) {
		// printf("Position %lu, 1s: %d, 0s %d\n", x, *(ones+x), *(zeros+x));
		temp <<= 1;
		if (getGamma) temp |= (*(ones+x) > *(zeros+x)) ? 0x1 : 0x0;
		else          temp |= (*(ones+x) > *(zeros+x)) ? 0x0 : 0x1;
	}
	return temp;
}

int main(int argc, char* argv[]) {

	FILE* fp = fopen("03\\input.txt", "r");

	char buff[BUFF_SZ] = {0};
	fgets(buff, BUFF_SZ, fp);
	size_t data_width = strlen(buff)-1; //Ignore trailing '\n'
	int* ones = calloc(data_width, sizeof(int));
	int* zeros = calloc(data_width, sizeof(int));
	incrementCounts(buff, ones, zeros);
	memset(buff, 0, BUFF_SZ);

	while (fgets(buff, BUFF_SZ, fp)) {
		incrementCounts(buff, ones, zeros);
	}

	size_t gamma_rate = determineRate(data_width, ones, zeros, true);
	size_t epsilon_rate = determineRate(data_width, ones, zeros, false);

	fprintf(stdout, "Gamma: %lu\nEpsilon: %lu\nProduct: %lu\n", gamma_rate, epsilon_rate, gamma_rate*epsilon_rate);

	fclose(fp);
}