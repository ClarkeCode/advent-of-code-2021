#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_SZ 1000
#define BUFF_SZ 128

typedef struct {
	size_t* ones;
	size_t* zeros;
	size_t data_width;
} BitCounter;

size_t value_from_binary_str(char* buff) {
	size_t temp = 0;
	for (; *buff != '\0'; buff++) {
		temp <<= 1;
		temp |= *buff == '1';
	}
	return temp;
}

char* fgetline(FILE* fp, char* buff) {
	if (!fgets(buff, BUFF_SZ, fp)) return NULL;
	if (buff[strlen(buff)-1] == '\n')
		buff[strlen(buff)-1] = '\0';
	return buff;
}


void incrementCounter(BitCounter* counter, char* buff) {
	for (size_t offset = 0; buff[offset] != '\0'; offset++) {
		if (buff[offset] == '1') counter->ones[offset]++;
		else                     counter->zeros[offset]++;
	}
}

char* leastCommonFromCounter(BitCounter* counter, char* buff) {
	for (size_t x = 0; x < counter->data_width; x++) {
		size_t count_1 = *(counter->ones+x);
		size_t count_0 = *(counter->zeros+x);

		*buff++ = (count_1 < count_0) ? '1' : '0';
	}
	return buff;
}
char* mostCommonFromCounter(BitCounter* counter, char* buff) {
	for (size_t x = 0; x < counter->data_width; x++) {
		size_t count_1 = *(counter->ones+x);
		size_t count_0 = *(counter->zeros+x);

		*buff++ = (count_1 >= count_0) ? '1' : '0';
	}
	return buff;
}

bool matchesFirstN(char* item, char* control, size_t n) { return strncmp(item, control, n) == 0; }

int main(int argc, char* argv[]) {

	BitCounter counter = {0};

	FILE* fp = fopen("03\\input.txt", "r");

	size_t lines = 0;
	char data[INPUT_SZ][BUFF_SZ] = {0};

	char buff[BUFF_SZ] = {0};
	fgetline(fp, data[0]);
	size_t data_width = strlen(data[0]);

	counter.data_width = data_width;
	counter.ones = calloc(data_width, sizeof(int));
	counter.zeros = calloc(data_width, sizeof(int));
	
	incrementCounter(&counter, data[lines]);
	lines++;

	while (fgetline(fp, data[lines])) {
		incrementCounter(&counter, data[lines]);
		lines++;
	}

	// fprintf(stdout, "Gamma: %lu\nEpsilon: %lu\nProduct: %lu\n", gamma_rate, epsilon_rate, gamma_rate*epsilon_rate);

	for (size_t x = 0; x < counter.data_width; x++) {
		fprintf(stdout, "%3lu - %3lu\n", *(counter.ones+x), *(counter.zeros+x));
	}

	char mostCommon[BUFF_SZ] = {0};
	char leastCommon[BUFF_SZ] = {0};
	mostCommonFromCounter(&counter, mostCommon);
	leastCommonFromCounter(&counter, leastCommon);

	bool foundMatch = false;
	char* oxygen;

	for (size_t x = 0; x < counter.data_width; x++) {
		for (size_t line_index = 0; line_index < INPUT_SZ; line_index++) {
			bool doesMatch = matchesFirstN(data[line_index], mostCommon, x+1);
			if (!foundMatch && doesMatch) {foundMatch = true; oxygen = data[line_index]; }
			else if (foundMatch && doesMatch) {foundMatch = false; x++; line_index = -1; }
		}
	}

	foundMatch = false;
	char* co2;

	for (size_t x = 0; x < counter.data_width; x++) {
		for (size_t line_index = 0; line_index < INPUT_SZ; line_index++) {
			bool doesMatch = matchesFirstN(data[line_index], mostCommon, x+1);
			if (!foundMatch && doesMatch) {foundMatch = true; co2 = data[line_index]; }
			else if (foundMatch && doesMatch) {foundMatch = false; x++; line_index = -1; }
		}
	}


	printf("%lu\n%lu\n%lu\n", value_from_binary_str(oxygen), value_from_binary_str(co2), value_from_binary_str(oxygen)*value_from_binary_str(co2));

	if (counter.ones) free(counter.ones);
	if (counter.zeros) free(counter.zeros);
	fclose(fp);
}