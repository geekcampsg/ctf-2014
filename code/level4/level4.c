#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	time_t utctime;
	struct tm *curtime;
	char buf[80];

	srand(time(NULL));

	time(&utctime);
	curtime = localtime(&utctime);

	strftime(buf, sizeof(buf), "It's %H:%M:%S on %d-%m-%Y. ", curtime);
	puts(buf);
	printf("Your random number of the day is %d.\n", rand());

	return 0;
}
