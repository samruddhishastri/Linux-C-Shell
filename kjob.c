#include"headerfiles/headers.h"
#include"headerfiles/kjob.h"

void kjob(char arg[]){
	if(strcmp(arg, "kjob")==0){
		printf("Invalid number of arguments passed\n");
		return;
	}

	char *token = strtok(arg, " ");
	token = strtok(NULL, " ");
	int job_no = atoi(token), sig_no;
	token = strtok(NULL, " ");
	if(token==NULL){
		printf("Invalid number of arguments passed\n");
		return;	
	}
	else{
		sig_no = atoi(token);
		token = strtok(NULL, " ");
	}
	if(token!=NULL){
		printf("Invalid number of arguments passed\n");
		return;	
	}

	kjob_pid = job_no;

	kill(job_arr[job_no].pid, sig_no);

	if(!(sig_no >=17 && sig_no <=22)){
		fprintf(stderr, "%s with pid %d exited abnormally\n", job_arr[job_no].name, job_arr[job_no].pid);
		for(int j=job_no+1; j<=count; j++){
	      	strcpy(job_arr[j-1].name, job_arr[j].name);
	      	job_arr[j-1].pid = job_arr[j].pid;
	    }
	    count--;
	}

}