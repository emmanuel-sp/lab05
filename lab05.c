#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Convert to binary
void toBinary(int bits, int n, char bin[]);
//Convert to two's complement
void twosComp(int bits, char bin[]);
//Convert to decimal
void toInt(int nums[], char * binary);

int main(int argc, char * argv[]) {
	int bits = 0;
	int decimal = -1;
	char * binary = "ok";

	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-bits") == 0) {
			bits = atoi(argv[i + 1]);
		}
		if (strcmp(argv[i], "-decimal") == 0) {
			decimal = atoi(argv[i + 1]);
		}
		if (strcmp(argv[i], "-binary") == 0) {
			binary = argv[i + 1];
		}
	}

	char bin[64] = {'0'};
	int nums[1] = {0};
	if (decimal == -1) {
		bits = strlen(binary);
	}
	toBinary(bits, decimal, bin);
	toInt(nums, binary);

	if (decimal != -1) {
		printf("%d in decimal is equal to %s in binary using %d-bit two's complement representation\n"
		,decimal, bin, bits);
	} else {
		printf("%s in binary is equal to %d in decimal using %d-bit two's complement representation\n",
		binary, nums[0], bits);
	}

	return 0;
}

void toInt(int nums[], char * binary) {
    int count = 1;
    int i;
    int is_negative = (binary[0] == '1');

    nums[0] = 0;

    for (i = strlen(binary) - 1; i >= is_negative; i--) {
        nums[0] += count * (binary[i] - '0');
        count *= 2;
    }

    if (is_negative) {
        nums[0] -= count;  // Subtract count from the result if the number is negative
    }
}

//void toInt(int nums[], char * binary) {
//	int count = 1;
//	for (int i = strlen(binary); i > 0; i--) {
//		nums[0] += count * (binary[i] + '0');
//		count *= 2;
//	}
//	nums[0] -= count * (binary[0] + '0');
//}

void toBinary(int bits, int n, char bin[]) {
	int res = n > 0 ? n : -1 * n;
	for (int i = bits - 1; i > 0; i--) {
		bin[i] = res % 2 + '0';
		res /= 2;
	}
	bin[0] = '0';
	if (n < 0) {
		twosComp(bits, bin);
	}
}

void twosComp(int bits, char bin[]) {
	for (int i = bits - 1; i > -1; i--) {
		if (bin[i] == '1') {
			bin[i] = '0';
		} else if (bin[i] == '0') {
			bin[i] = '1';
		}
	}

	int i = bits - 1;
	while (i > -1 && bin[i] == '1') {
		bin[i] = '0';
		i -= 1;
	}
	bin[i] = '1';

}
