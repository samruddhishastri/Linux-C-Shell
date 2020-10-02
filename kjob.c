#include"headerfiles/headers.h"
#include"headerfiles/kjob.h"

void kjob(char arg[]){
	if(strcmp(arg, "kjob")==0){
		printf("Invlid number of arguments passed\n");
		return;
	}

	char *token = strtok(arg, " ");
	token = strtok(NULL, " ");
	int job_no = atoi(token), sig_no;
	token = strtok(NULL, " ");
	if(token==NULL){
		printf("Invlid number of arguments passed\n");
		return;	
	}
	else{
		sig_no = atoi(token);
		token = strtok(NULL, " ");
	}
	if(token!=NULL){
		printf("Invlid number of arguments passed\n");
		return;	
	}

	kjob_pid = job_no;

	kill(job_arr[job_no].pid, sig_no);	
}