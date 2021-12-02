#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFF_SZ 256

typedef struct {
	size_t horizontal, depth, aim;
} Position;

bool processCommand(FILE* fp, Position* pos) {
	char buff[BUFF_SZ] = {0};
	if (!fgets(buff, BUFF_SZ, fp)) { return false; }

	if (strncmp(buff, "forward", 7) == 0) {
		size_t value = atoi(buff+7);
		pos->horizontal += value;
		if (pos->aim != 0) pos->depth += pos->aim * value; 
	}
	if (strncmp(buff, "up",      2) == 0) { pos->aim      -= (size_t)atoi(buff+2); }
	if (strncmp(buff, "down",    4) == 0) { pos->aim      += (size_t)atoi(buff+4); }

	return true;
}

int main (int argc, char* argv[]) {
	FILE* fp = fopen("02\\input.txt", "r");
	if (!fp) fprintf(stderr, "ERROR: Cannot open input file\n");

	Position pos = {0};
	while (processCommand(fp, &pos)) {}

	fclose(fp);

	fprintf(stdout, "Depth: %lu, Progress: %lu\nProduct: %lu\n", pos.depth, pos.horizontal, pos.depth * pos.horizontal);
}