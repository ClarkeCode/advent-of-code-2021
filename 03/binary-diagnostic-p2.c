#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_SZ 1000
#define BUFF_SZ 128

typedef struct {
	size_t ones;
	size_t zeros;
} BitCounter;

char data[INPUT_SZ][BUFF_SZ] = {0};
bool selected[INPUT_SZ] = {0};

void get_count_from_valid_bytes(BitCounter* counter, bool* validity, size_t bit_index) {
	for (size_t line_idx = 0; line_idx < INPUT_SZ; line_idx++) {
		if (!(*(validity+line_idx))) continue;
		if (*(data[line_idx]+bit_index) == '1') counter->ones++;
		if (*(data[line_idx]+bit_index) == '0') counter->zeros++;
	}
}

bool get_greater(BitCounter* counter, char value, char tiebreak) {
	if (counter->ones == counter->zeros && value == tiebreak) return true;
	else if (counter->ones > counter->zeros && value == '1') return true;
	else if (counter->ones < counter->zeros && value == '0') return true;
	return false;
}

bool get_lesser(BitCounter* counter, char value, char tiebreak) {
	if (counter->ones == counter->zeros && value == tiebreak) return true;
	else if (counter->ones < counter->zeros && value == '1') return true;
	else if (counter->ones > counter->zeros && value == '0') return true;
	return false;
}

void filter_on_bit(BitCounter* counter, bool* validity, size_t bit_index, bool (*predicate)(BitCounter*, char, char), char tiebreak) {
	for (size_t line_idx = 0; line_idx < INPUT_SZ; line_idx++) {
		if (!(*(validity+line_idx))) continue;
		
		if (!predicate(counter, data[line_idx][bit_index], tiebreak)) *(validity+line_idx) = false;
	}
}

size_t countBool(bool* values, size_t sz) {
	size_t count = 0;
	for (size_t x = 0; x < sz; x++) {
		if (*(values+x)) count++;
	}
	return count;
}


char* get_oxygen(bool* validity) {
	size_t bit_index = 0;
	while (countBool(validity, INPUT_SZ) != 1) {
		BitCounter count = {0};
		get_count_from_valid_bytes(&count, validity, bit_index);
		filter_on_bit(&count, validity, bit_index, &get_greater, '1');
		bit_index++;
	}

	size_t idx = 0;
	while (!(*validity++)) { idx++; }
	char* selected = data[idx];
	return selected;
}

char* get_co2(bool* validity) {
	size_t bit_index = 0;
	while (countBool(validity, INPUT_SZ) != 1) {
		BitCounter count = {0};
		get_count_from_valid_bytes(&count, validity, bit_index);
		filter_on_bit(&count, validity, bit_index, &get_lesser, '0');
		bit_index++;
	}

	size_t idx = 0;
	while (!(*validity++)) { idx++; }
	char* selected = data[idx];
	return selected;
}



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



bool matchesFirstN(char* item, char* control, size_t n) { return strncmp(item, control, n) == 0; }

int main(int argc, char* argv[]) {

	FILE* fp = fopen("03\\input.txt", "r");

	size_t lines = 0;
	char buff[BUFF_SZ] = {0};
	fgetline(fp, data[0]);
	size_t data_width = strlen(data[0]);
	lines++;

	while (fgetline(fp, data[lines])) { lines++; }

	memset(selected, 1, INPUT_SZ);
	char* oxygen = get_oxygen(selected);
	memset(selected, 1, INPUT_SZ);
	char* co2 = get_co2(selected);
	fprintf(stdout, "%s\n%s\n%lu\n", oxygen, co2, value_from_binary_str(oxygen) * value_from_binary_str(co2));

	fclose(fp);
}