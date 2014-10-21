#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	printf("System info: ");
	fflush(stdout);
	system("uname -a");
	return 0;
}
