#include"headerfiles/headers.h"
#include"headerfiles/pinfo.h"

void getinfo(int pid, char wd[]){

	char exe[256], status[256];
	sprintf(status,"/proc/%d/status", pid);
	sprintf(exe, "/proc/%d/exe", pid);
	FILE *f = fopen(status, "r");
	
	char *line = NULL;
    size_t len = 0;
    ssize_t read;

	if(f == NULL){
		printf("This process id does not exist.\n");
		return;
	}

	int i=0;
	char state[40], size[40];
	while ((read = getline(&line, &len, f)) != -1) {
       i++;
		if(i==3){
        	strcpy(state, line);
			char *token = strtok(state, "\t");
			token = strtok(NULL, " ");
			strcpy(state, token);
		}
		if(i==18){
        	strcpy(size, line);
			char *token = strtok(size, " ");
			token = strtok(NULL, " ");
			strcpy(size, token);
		}
	}
	
	printf("pid -- %d\nProcess Status -- %s\nmemory -- %s\nExecutable Path -- ", pid, state, size);

	char path[2048];
	int val = readlink(exe, path, 1000);

	if(val == -1)
		printf("No path for executable\n");
	
	else{
		path[val] = '\0';
		
		char *p = strstr(path, wd);
		if(p){
			p += strlen(wd);
			printf("~%s\n", p);
		}
		else{
			printf("~%s\n", path);
		}
	}
	
	fclose(f);
    if (line)
        free(line);

}

void pinfo(char arg[], char wd[]){

	char *token = strtok(arg, " ");
	token = strtok(NULL, " ");
	int arr[256];

	if(token==NULL){
		char status[256], exe[256];
		int pid = getpid();
		getinfo(pid, wd);
	}

	else{
		int k = 0;
		while(token!=NULL){
			arr[k] = atoi(token);
			k++;
			token = strtok(NULL, " ");
		}

		for(int i=0; i<k; i++){
			getinfo(arr[i], wd);
		}

	}
}