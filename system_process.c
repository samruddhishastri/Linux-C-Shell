#include"headerfiles/headers.h"
#include"headerfiles/system_process.h"
#include"headerfiles/bg_signal.h"

void bg_func(char **d){
	count++;
    pid_t pid;
    pid = fork(); 
    setpgid(0, 0);
    strcpy(job_arr[count].name, d[0]);
    job_arr[count].pid = pid;
    if(pid == 0){
     	if (signal(SIGTSTP, bg_signal));
     	int ret = execvp(d[0], d);
        if(ret == -1){
            perror("Error");
        }
        exit(0);
    }
}

void fg_func(char **d){
    pid_t pid;
    pid = fork();
    if(pid == 0){
    	int ret = execvp(d[0], d);
        if(ret == -1)
            perror("Error");
        exit(0);
    }
    else{
        int status;
        fg_process = pid;
        waitpid(pid, &status, WUNTRACED);
    }
}

void system_process(char arg[]){
	
	char a[256];
	strcpy(a, arg);
	
	int flag=0;
	int j=0;
	for(int i=0; i<strlen(arg); i++){
		if(arg[i] == '&'){
			flag=1;
			//strcpy(a[i], '\0');
		}
		else{
			a[j++] = a[i];
		}
	}

	a[j] = '\0';
	
	char* token;
     char ** args = malloc(100*sizeof(char*));

    token  = strtok(a," ");
    int i=0;
    while(token!=NULL)
    {
        args[i++] = token;
        token  = strtok(NULL," ");
    }
    args[i] = NULL;

	if(flag == 1){
		bg_func(args);
	}

	else{
		fg_func(args);
	}
}

