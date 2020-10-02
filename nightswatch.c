#include"headerfiles/headers.h"
#include"headerfiles/nightswatch.h"

int kbhit(){
	return 0;
}

void interrupt(){
	FILE *fd = fopen("/proc/interrupts", "r");
	if(fd==NULL){
		printf("Cannot open /proc/interrupts file\n");
	}
	else{
		char line[256];
		int i=0;
		while(fgets(line, sizeof(line), fd)!=NULL){
			if(i==2){
				break;
			}
			i++;
		}

        char *token = strtok(line, ":");
        token = strtok(NULL, "I");
        printf("     %s\n",token);
	}
}

void newborn(){
	FILE *fd = fopen("/proc/loadavg", "r");
	if(fd==NULL){
		printf("Cannot open /proc/loadavg file\n");
	}
	else{
		char line[256], x[256];
		fgets(line, sizeof(line), fd);
		char *token = strtok(line, " ");
		while(token!=NULL){
			strcpy(x, token);
			token = strtok(NULL, " ");
		}
		printf("%s", x);
	}
}

void nightswatch(char arg[]){

	char *token = strtok(arg, " ");
	token = strtok(NULL, " ");

	if((token==NULL) || strcmp(token, "-n")!=0){
		printf("Invalid\n");
		return;
	}

	else{
		token = strtok(NULL, " ");
		int time = atoi(token);

		token = strtok(NULL, " ");

		int flag=0;

		if(strcmp(token, "interrupt")==0){
			flag = 1;
			FILE *fd = fopen("/proc/interrupts", "r");
			if(fd==NULL){
				printf("Cannot open /proc/interrupts file\n");
			}
			else{
				char line[256];
				int i=0;
				while(fgets(line, sizeof(line), fd)!=NULL){
					if(i==0){
						printf("%s", line);
						break;
					}
				}
				i++;
				fclose(fd);
			}
		}

		else if(strcmp(token, "newborn")==0){
			flag = 2;
		}

		else{
			printf("Invalid\n");
			return;
		}

		while(1){

			if(kbhit()){
				break;
			}

			if(flag==1){
				interrupt();
			}

			if(flag==2){
				newborn();
			}

			sleep(time);
		}

	}

}