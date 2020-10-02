#include"headerfiles/headers.h"
#include"headerfiles/echo.h"

void echo(char arg[]){
	char arg1[256];
	strcpy(arg1, arg);
	
	char *cmd = strtok(arg1, " ");

	int i=0, stop=0;
	char remainder[256];

	while(cmd[i] == arg[i]){
		i++;
		if(arg[i] == '\0')
			stop=1;
	}
	if(!stop)
		strcpy(remainder, &arg[i+1]);

	printf("%s\n", remainder);
}
