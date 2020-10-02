#include"headerfiles/headers.h"
#include"headerfiles/cd.h"

void cd(char arg[], char wd[]){

	char arg1[256];
	strcpy(arg1, arg);
	
	char *cmd = strtok(arg1, " ");

	int i=0, stop=0, pre_variable;
	char remainder[256], dir[256];

	while(cmd[i] == arg[i]){
		i++;
		if(arg[i] == '\0')
			stop=1;
	}
	if(!stop)
		strcpy(remainder, &arg[i+1]);

	strcpy(arg, remainder);

	char cwd[256]={'\0'};
	getcwd(cwd, sizeof(cwd));

	if((strcmp(cwd, wd)==0) && (strcmp(arg, "..")==0)){
		getcwd(prev_directory, sizeof(prev_directory));
		pre_variable = variable;
		chdir("..");
		variable = 1;
		return;
	}
	
	if((strcmp(arg, "~")==0)){
		getcwd(dir, sizeof(dir));
		int r = chdir(wd);
		if(r==-1){
			printf("Error Number %d\n", errno);
			perror("Directory");
			return;
		}
		strcpy(prev_directory, dir);
		pre_variable = variable;
		variable=0;
		return;
	}

	if((strcmp(arg, "-")==0)){
		getcwd(dir, sizeof(dir));
		printf("%s\n", prev_directory);
		int r = chdir(prev_directory);
		if(r==-1){
			printf("Error Number %d\n", errno);
			perror("Directory");
			return;
		}
		strcpy(prev_directory, dir);
		int temp = pre_variable;
		pre_variable = variable;
		variable = temp;
		return;
	}

	if(strcmp(arg, ".")==0 || strcmp(arg, "")==0);

	else{

		getcwd(dir, sizeof(dir));

		char *token = strtok(arg, "/");

		while(token!=NULL){

			char val[256];
			strcpy(val, token);

			token = strtok(NULL, "/");
			
			if(token==NULL){
				if(strcmp(val, "~")==0){
					chdir(wd);
					strcpy(prev_directory, dir);
					break;
				}
				getcwd(cwd, sizeof(cwd));
				if(strcmp(cwd, wd)==0 && strcmp(val, "..")==0){
					variable=1;
				}
				int r = chdir(val);
				if(r==-1){
					printf("Error Number %d\n", errno);
					perror("Directory");
					break;
				}
				strcpy(prev_directory, dir);
				break;
			}
			int r;
			
			if(strcmp(val, "~")==0){
				r = chdir(wd);
			}

			else{
				getcwd(cwd, sizeof(cwd));
				if(strcmp(cwd, wd)==0 && strcmp(val, "..")==0){
					variable=1;
				}
				r = chdir(val);
			}

			if(r==-1){
				printf("Error Number %d\n", errno);
				perror("Directory");
				break;
			}
		}

		strcpy(prev_directory, dir);
	}
	
}