#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int ret = rmdir("del");
	if (ret == -1) {
		perror("rmdir");
		exit(1);
	}
	

	return 0;
}
