#include"headerfiles/headers.h"
#include"headerfiles/env_var.h"

void setenv_func(char arg[]){
	if(strcmp(arg, "setenv")==0){
		printf("Invalid number of arguments passed\n");
		return;
	}

	char var[40], val[256];
	char *token = strtok(arg, " ");
	token = strtok(NULL, " ");
	strcpy(var, token);
	token = strtok(NULL, " ");
	if(token!=NULL){
		strcpy(val, token);
		token = strtok(NULL, " ");
	}
	else{
		val[0] = '\0';
	}
	if(token!=NULL){
		printf("Invalid number of arguments passed\n");
		return;
	}
	int x = setenv(var, val, 1);
	if(x<0){
		printf("Error number %d\n", errno);
		perror("Setenv:");
	}
}

void unsetenv_func(char arg[]){
	if(strcmp(arg, "unsetenv")==0){
		printf("Invalid number of arguments passed\n");
		return;
	}
	char var[40];
	char *token = strtok(arg, " ");
	token = strtok(NULL, " ");
	strcpy(var, token);
	token = strtok(NULL, " ");
	if(token!=NULL){
		printf("Invalid number of arguments passed");
		return;
	}
	int x = unsetenv(var);
	if(x<0){
		printf("Error number %d\n", errno);
		perror("Unsetenv:");
	}
}

