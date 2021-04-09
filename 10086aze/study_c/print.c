#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, const char *argv[])
{
	int i;
        for(i=1;i;i++){
            sleep(1);
        printf("\b\b\b\b\b%d",i);
		fflush(stdout);
	}
	return 0;
}
