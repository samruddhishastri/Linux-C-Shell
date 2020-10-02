#include"headerfiles/headers.h"
#include"headerfiles/fg_bg.h"

void bg(char arg[]){
	char *token = strtok(arg, " ");
	int arr[20], i=0;
	token = strtok(NULL, " ");
	if(token==NULL){
		printf("Incorrect number of arguments\n");
		return;
	}
	while(token!=NULL){
		arr[i] = atoi(token);
		i++;
		token = strtok(NULL, " ");
	}

	for(int j=0; j<i; j++){
		if(arr[j] <= count){
			kill(job_arr[arr[j]].pid, SIGTTIN);  
        	kill(job_arr[arr[j]].pid, SIGCONT);
		}
		else{
			printf("No background process with the given ID exists\n");
		}
	}
}

void fg(char arg[]){
	char *token = strtok(arg, " ");
	int arr[20], i=0;
	token = strtok(NULL, " ");
	if(token==NULL){
		printf("Incorrect number of arguments\n");
		return;
	}

	while(token!=NULL){
		arr[i] = atoi(token);
		i++;
		token = strtok(NULL, " ");
	}

	for(int j=0; j<i; j++){
		if(arr[j] <= count){
			int pid = job_arr[arr[j]].pid;
			signal(SIGTTIN, SIG_IGN);
           	signal(SIGTTOU,SIG_IGN);
            tcsetpgrp(0,pid);
            for(int k=arr[j]+1; k<=count; k++){
	      		strcpy(job_arr[k-1].name, job_arr[k].name);
	      		job_arr[k-1].pid = job_arr[k].pid;
	      	}
	      	count--;
	      	kill(pid, SIGCONT);
	      	waitpid(pid, NULL, WUNTRACED);
            tcsetpgrp(0,getpgrp());
            signal(SIGTTIN,SIG_DFL);
            signal(SIGTTOU,SIG_DFL);
            fg_process = pid;
		}
		else{
			printf("No background process with the given ID exists\n");
		}
	}
}