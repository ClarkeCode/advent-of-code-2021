#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SZ 256

int main (int argc, char* argv[]) {
	FILE* fp = fopen("01\\input.txt", "r");
	if (!fp) fprintf(stderr, "ERROR: Cannot open input file\n");

	char buff[BUFF_SZ] = {0};
	fgets(buff, BUFF_SZ, fp);
	if (strlen(buff) == 0) fprintf(stderr, "ERROR: No initial value\n");

	size_t num_depth_increases = 0;
	int prevMeasurement = atoi(buff);
	memset(buff, 0, BUFF_SZ);
	int currMeasurement = 0;
	while (fgets(buff, BUFF_SZ, fp)) {
		currMeasurement = atoi(buff);
		memset(buff, 0, BUFF_SZ);
		if (currMeasurement > prevMeasurement) {
			num_depth_increases++;
		}
		prevMeasurement = currMeasurement;
	}
	fclose(fp);

	fprintf(stdout, "The depth measurement increases %lu times\n", num_depth_increases);
}