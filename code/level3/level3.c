#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef void (*func)(const char *);

char rotn(char c, int n)
{
	if (isalpha(c)) {
		char base = islower(c) ? 'a' : 'A';
		return (c - base + n) % 26 + base;
	}
	return c;
}

void rotm1(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], -1));
	}
	printf("\n");
}

void rot0(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 0));
	}
	printf("\n");
}

void rot1(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 1));
	}
	printf("\n");
}

void rot2(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 2));
	}
	printf("\n");
}

void rot3(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 3));
	}
	printf("\n");
}

void rot4(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 4));
	}
	printf("\n");
}

void rot5(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 5));
	}
	printf("\n");
}

void rot6(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 6));
	}
	printf("\n");
}

void rot7(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 7));
	}
	printf("\n");
}

void rot8(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 8));
	}
	printf("\n");
}

void rot9(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 9));
	}
	printf("\n");
}

void rot10(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 10));
	}
	printf("\n");
}

void rot11(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 11));
	}
	printf("\n");
}

void rot12(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 12));
	}
	printf("\n");
}

void rot13(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 13));
	}
	printf("\n");
}

void rot14(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 14));
	}
	printf("\n");
}

void rot15(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 15));
	}
	printf("\n");
}

void rot16(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 16));
	}
	printf("\n");
}

void rot17(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 17));
	}
	printf("\n");
}

void rot18(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 18));
	}
	printf("\n");
}

void rot19(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 19));
	}
	printf("\n");
}

void rot20(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 20));
	}
	printf("\n");
}

void rot21(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 21));
	}
	printf("\n");
}

void rot22(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 22));
	}
	printf("\n");
}

void rot23(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 23));
	}
	printf("\n");
}

void rot24(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 24));
	}
	printf("\n");
}

void rot25(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 25));
	}
	printf("\n");
}

void rot26(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 26));
	}
	printf("\n");
}

void rot27(const char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
		putchar(rotn(str[i], 27));
	}
	printf("\n");
}

void run(const char *str) { system(str); }

int main(int argc, char **argv)
{
	run("/usr/bin/uname -a");

	if (argc != 3) {
		printf("Usage: level3 <rot_offset> <string>\n");
		printf("Example:\n $ level3 13 foo\nsbb\n");
		return 1;
	}

	func _rot = (&rot0 + (atoi(argv[1]) * (&rot1 - &rot0)));
	_rot(argv[2]);
	return 0;
}
