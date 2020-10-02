#include"headerfiles/headers.h"
#include"headerfiles/show_jobs.h"

void show_jobs(){
	char status[256], state[5];

	for(int i=1; i<=count; i++){
		sprintf(status,"/proc/%d/status", job_arr[i].pid);
		FILE *f = fopen(status, "r");
		if(f == NULL){
			return;
		}
		char *line = NULL;
    	size_t len = 0;
    	ssize_t read;
    	int j=0;
		while ((read = getline(&line, &len, f)) != -1) {
       		j++;
			if(j==3){
        		strcpy(state, line);
				char *token = strtok(state, "\t");
				token = strtok(NULL, " ");
				strcpy(state, token);
				break;
			}
		}

		free(line);
		if(strcmp(state,"T")==0)
			printf("[%d] Stopped %s [%d]\n", i, job_arr[i].name, job_arr[i].pid);
		else{
			printf("[%d] Running %s [%d]\n", i, job_arr[i].name, job_arr[i].pid);
		}
	}		
}