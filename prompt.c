#include "headerfiles/headers.h"
#include"headerfiles/prompt.h"

void prompt(char wd[]){
	
	char hostname[256];
	char username[256];
	char cwd[256];

	gethostname(hostname, sizeof(hostname));
	getlogin_r(username, sizeof(username));
	getcwd(cwd, sizeof(cwd));
	char relative_path[256];

	if(strcmp(cwd, wd)==0){
		variable=0;
	}

	if(variable){
		strcpy(relative_path, cwd);
	}

	else{

		int n = strlen(wd), k=0;
		relative_path[0] = '\0';
	
		for(int i=n; i<strlen(cwd); i++){
			relative_path[k] = cwd[i];
			k++;
		}

		relative_path[k] = '\0';
	}

	printf("\033[1;33m%s@%s", username, hostname);
	printf("\033[0m:");
	printf("\033[1;36m~%s", relative_path);
	printf("\033[0m");
	printf("$ ");
}
