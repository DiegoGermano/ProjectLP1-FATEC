#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;
	printf("Content-type: text/plain\n\n");

	printf("DIEGO GERMANO");

	for(i=1; i<argc; i++)
	{
		if(argv[i] != '\0')
			printf("Saida: %s \n", argv[i]);
	}
	return 0;
}
