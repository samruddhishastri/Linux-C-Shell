#include"headerfiles/headers.h"
#include"headerfiles/pwd.h"
#include"headerfiles/cd.h"
#include"headerfiles/echo.h"
#include"headerfiles/takeinput.h"
#include"headerfiles/system_process.h"
#include"headerfiles/pinfo.h"
#include"headerfiles/ls.h"
#include"headerfiles/history.h"
#include"headerfiles/nightswatch.h"
#include"headerfiles/man.h"
#include"headerfiles/bg_signal.h"
#include"headerfiles/env_var.h"
#include"headerfiles/show_jobs.h"
#include"headerfiles/kjob.h"
#include"headerfiles/overkill.h"
#include"headerfiles/fg_bg.h"

int saved_stdout, saved_stdin, beta;
char token1[256][256];

struct pair{
    char command[256];
    char input[256];
    char output[256];
};
struct pair b;

void removespaces(char *arr, int n){
	int space=0, k=0;

	for(int i=0; i<n; i++){
		while(k==0 && i<n && ((arr[i] == ' ') || (arr[i] == '\t') || (arr[i] == '\r'))){
			i++;
		}

		if(arr[i] == ' ' || arr[i] == '\t' || arr[i] == '\r'){
			if(!space){
				arr[k++] = ' ';
				space = 1;
			}
		}
		else{
			arr[k++] = arr[i];
			space = 0;
		}

        if(arr[i]=='\n'){
            arr[i] = '\0';
            break;
        }
	}
	arr[k-1] = '\0';
	int x = k-1;

	if(arr[k-2]==' '){
		arr[k-2] = '\0';
		x=k-2;
	}
}

void piping(char command[]){
	beta = 0;
	char *token = strtok(command, "|");
	while(token!=NULL){
		strcpy(token1[beta], token);
		beta++;
		token = strtok(NULL, "|");
	}

	for(int i=0; i<beta; i++){
		removespaces(token1[i], strlen(token1[i])+1);
	}
}

void redirection(char str[]){

	saved_stdout = dup(1);
	saved_stdin = dup(0);

	char *copy = strdup(str);
	char *token = strtok(str, "><");
	strcpy(b.command, token);
	
	if(strcmp(token, copy)==0){
		b.input[0]='\0';
		b.output[0]='\0';
	}

	else if(copy[token-str+strlen(token)]=='<'){
		token = strtok(NULL, ">");
		strcpy(b.input, token);
		token = strtok(NULL, "\0");
		if(token!=NULL){
			strcpy(b.output, token);
		}

		else{
			b.output[0] = '\0';	
		}
	}

	else{
		token = strtok(NULL, "<");
		strcpy(b.output, token);
		token = strtok(NULL, "\0");
		if(token!=NULL){
			strcpy(b.input, token);
		}
		else{
			b.input[0] = '\0';		
		}
	}

	if(b.output[0]=='>'){
		for(int i=1; i<strlen(b.output); i++){
			b.output[i-1] = b.output[i];
		}
		b.output[strlen(b.output)-1] = '\0';
	}

	removespaces(b.command, strlen(b.command)+1), removespaces(b.input, strlen(b.input)+1), removespaces(b.output, strlen(b.output)+1);

	if(b.input[0]!='\0'){
		int fd;
		fd = open(b.input, O_RDONLY);
		if(fd<0){
			printf("Error");
		}
		dup2(fd, 0);
	}
	
	if(b.output[0]!='\0'){
		int fd;
		if(strstr(copy, ">>")==NULL){
			fd = open(b.output, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else{
			fd = open(b.output, O_CREAT | O_WRONLY | O_APPEND, 0644);	
		}

		if(fd<0){
			printf("Error");
		}
		dup2(fd, 1);
	}
}

void execute(char t[], char wd[]){
	//printf("blah");
	char cmd[256];
	strcpy(cmd, t);
	redirection(cmd);
	char *x = strtok(cmd, " ");
	strcpy(t, b.command);

	if(strcmp(x, "pwd")==0){
		pwd(wd);
	}

	else if(strcmp(x, "ls")==0 || strcmp(x, "l")==0){
		ls(t, wd);
	}

	else if(strcmp(x, "quit")==0){
		exit(0);
	}

	else if(strcmp(x, "pinfo")==0){
		pinfo(t, wd);
	}

	else if(strcmp(x, "history")==0){
		view_history(t, wd);
	}

	else if(strcmp(x, "nightswatch")==0){
		nightswatch(t);
	}

	else if(strcmp(x, "echo")==0){
		echo(t);
	}

	else if(strcmp(x, "cd")==0){
		cd(t, wd);
	}

	else if(strcmp(x, "man")==0){
		man();
	}

	else if(strcmp(x, "setenv")==0){
		setenv_func(t);
	}

	else if(strcmp(x, "unsetenv")==0){
		unsetenv_func(t);
	}

	else if(strcmp(t, "jobs")==0){
		show_jobs(t);
	}

	else if(strcmp(x, "kjob")==0){
		kjob(t);
	}

	else if(strcmp(t, "overkill")==0){
		overkill();
	}

	else if(strcmp(x, "bg")==0){
		bg(t);
	}

	else if(strcmp(x, "fg")==0){
		fg(t);
	}

	else{
		system_process(t);
	}

	dup2(saved_stdout, 1);
	close(saved_stdout);

	dup2(saved_stdin, 0);
	close(saved_stdin);
}

void takeinput(char wd[]){
    
    char *buffer=NULL;
    size_t bufsize = 100000;

    buffer = (char *)malloc(bufsize * sizeof(char));
    
    if( buffer == NULL){
        perror("Unable to allocate buffer");
        exit(1);
    }

    int characters = getline(&buffer,&bufsize,stdin);

    if(strcmp(buffer, "\0")==0){
      printf("\n");
      exit(0);
    }

    if(strcmp(buffer, "\n")==0){
        return;
    }
    
    //write_history(buffer, wd);

    char *token = strtok(buffer, ";");
    char token2[256][256];
    int k=0;

    while(token!=NULL){
        strcpy(token2[k], token);
        token = strtok(NULL, ";");
        k++;
    }

    for(int i=0; i<k; i++){
        removespaces(token2[i], strlen(token2[i])+5);
    }

    char cmd[256], a[256];
    int p1[2], p2[2];

    for(int j=0; j<k; j++){

    	if(strstr(token2[j], "|")!=NULL){

	        strcpy(a, token2[j]);
	        piping(a);
			int pipes = beta-1;

	        for(int i=0; i<beta; i++){
	       		if(i%2 != 0){
					if(pipe(p1)<0){
						perror("Pipe");
					}
				}
				else{
					if(pipe(p2)<0){
						perror("Pipe");
					}	
				}
				int pid = fork();
				if(pid==-1){
					perror("Error");
					break;
				}
				if(pid==0){
					if(i==0){
						dup2(p2[1], 1);
					}
					else if(i == pipes){
						if(i%2==0){
							dup2(p1[0], 0);
						}
						else{
							dup2(p2[0], 0);
						}
					}
					else{
						if(i%2==0){
							dup2(p1[0],0);
							dup2(p2[1],1);
						}
						else{
							dup2(p2[0],0);
							dup2(p1[1],1);
						}
					}

					execute(token1[i], wd);
					exit(0);
				}

				else{
					wait(NULL);
					if(i==0){
						close(p2[1]);
					}
					else if(i == pipes){
						if(pipes%2 ==0){
							close(p1[0]);
						}
						else{
							close(p2[0]);
						}
					}
					else{
						if(i%2==0){
					        close(p1[0]);
		            		close(p2[1]);
		        		}   
		        		else {
					        close(p2[0]);
		            		close(p1[1]);
		        		}
					}
				}
			}
		}

		else{
			execute(token2[j], wd);
		}
    }
}