#include"headerfiles/headers.h"
#include"headerfiles/pwd.h"

void pwd(char wd[]){
	char cwd[256];
	getcwd(cwd, sizeof(cwd));

	printf("Absolute Path: %s\n", cwd);
	int n = strlen(wd), k=0;

	char relative_path[256];
	
	for(int i=n; i<strlen(cwd); i++){
		relative_path[k] = cwd[i];
		k++;
	}
	
	relative_path[k] = '\0';
	
	if(variable==0){
		printf("Relative path: /home");
		printf("%s\n", relative_path);
	}
}