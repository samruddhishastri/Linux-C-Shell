#include"headerfiles/headers.h"
#include"headerfiles/system_process.h"

void system_process(char arg[]){
	
	char a[256];
	strcpy(a, arg);
	
	int flag=0;
	int j=0;
	for(int i=0; i<strlen(arg); i++){
		if(arg[i] == '&'){
			flag=1;
		}
		else{
			a[j++] = a[i];
		}
	}

	a[j] = '\0';
	
	char *token = strtok(arg, " ");
	char c[256], d[20][256];
	strcpy(c, token);
	token = strtok(NULL, " ");
	int flag1=0;
	int k=0;
	if(token==NULL){
		flag1 = 1;
	}

	else{
		do{
			if(token!=NULL && strcmp(token, "&")!=0){
				strcpy(d[k], token);
				k++;
			}
			token = strtok(NULL, " ");
		}while(token!=NULL);
		
		if(k==0){
			flag1 = 1;
		}
	}


	int x=0;

	int pid = fork();

	if(flag==1)
		setpgid(0,0);

	if(pid<0){
		printf("Error occurred during fork.\n");
		return;
	}

	if(pid==0){
		if(flag1==1){
			char *args[] = {c, NULL};
			int x = execvp(args[0], args);
			if(x==-1){
				printf("Incorrect command\n");
			}
		}
		else{
			char* args[256];
			args[0] = malloc(strlen(c));
            strcpy(args[0], c);
            int i;
			for(i=0; i<k+1; i++){
				args[i+1]=malloc(strlen(d[i]));
                strcpy(args[i+1], d[i]);
			}
			args[i] = NULL;
			int x = execvp(args[0], args);
			if(x==-1){
				printf("Incorrect command\n");
			}	
		}

	}

	else{
		if(x==-1){
			waitpid(pid, NULL, 0);
		}	
		else if(flag==0){
			fg_process = pid;
			strcpy(fg_name, job_arr[count].name);
			waitpid(pid, NULL, 0);
    	}
    	else{
    		count++;
    		printf("[%d] %d %s\n", count, pid, a);
    		job_arr[count].pid = pid;
	        strcpy(job_arr[count].name, a);
    	}
	}
}