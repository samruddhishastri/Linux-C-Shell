#include"headerfiles/headers.h"
#include"headerfiles/bg_signal.h"
#include"headerfiles/prompt.h"
#include"headerfiles/show_jobs.h"

void bg_signal(){
	//printf("blah");
	int status;
	pid_t p = waitpid(-1, &status, WNOHANG);
	for (int i = 1; i <= count; i++){
	    if (p < 0){
	      break;
	    }
	    char buff[20];
	    const int exit = WEXITSTATUS(status);
	    int ret = WIFEXITED(status);
	    if (ret && p == job_arr[i].pid || kjob_pid == job_arr[i].pid && p == job_arr[i].pid){
	    	if (exit == 0)
	        	strcpy(buff, "normally");
	      	else
	        	strcpy(buff, "abnormally");
	      	fprintf(stderr, "%s with pid %d exited %s\n", job_arr[i].name, p, buff);

	      	for(int j=i+1; j<=count; j++){
	      		strcpy(job_arr[j-1].name, job_arr[j].name);
	      		job_arr[j-1].pid = job_arr[j].pid;
	      	}
	      	count--;
	      	prompt(array);
	      	fflush(stdout);
	      	if(kjob_pid!=0){
	      		kjob_pid = 0;
	      	}
	    }
  	}

  	signal(SIGCHLD, bg_signal);
}

void interrupt_signal(){
    pid_t p = getpid();
    if (p != shellid)
        return;
    if (fg_process != -1){
        kill(fg_process, SIGINT);
        return;   
    }
    signal(SIGINT, interrupt_signal);
}

void stop_signal(){
	int p = getpid();
	if (p != shellid){
		return;
	}
	if (fg_process != -1){
		kill(fg_process, SIGTTIN);
		kill(fg_process, SIGTSTP);
		//show_jobs();
		//printf("fqwdjwy\n");
		count++;
		job_arr[count].pid = fg_process;
		strcpy(job_arr[count].name, fg_name);
		//show_jobs();
		//printf("djsduq\n");
		fg_process = -1;
		//prompt(array);
	}
	fflush(stdout);
	signal(SIGTSTP, stop_signal);
}