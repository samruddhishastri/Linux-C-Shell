#include"headerfiles/headers.h"
#include"headerfiles/history.h"

void write_history(char command[], char wd[]){
	char buff[256], hist[256][256];
	sprintf(buff, "%s/history.txt", wd);
	FILE *fd = fopen(buff,"r");

	if(fd==NULL){
		perror("File");
	}

	if(fd!=NULL){
		char line[256];
		int i=0;
		
		while (fgets(line, sizeof(line), fd) != NULL) {
			strcpy(hist[i], line);
			i++;
		}

		if(i==20){
			for(int j=0; j<19; j++){
				strcpy(hist[j], hist[j+1]);
			}
			i=19;
		}
		strcpy(hist[i], command);
		fclose(fd);
		fd = fopen(buff, "w");
		if(fd==NULL){
			perror("File");
		}
		for(int j=0; j<=i; j++){
			fprintf(fd, "%s", hist[j]);
		}
		fclose(fd);
	}

	else{
		fd = fopen(buff, "w+");
		if(fd==NULL){
			perror("File");
		}
		fprintf(fd, "%s", command);
		fclose(fd);
	}
}

void view_history(char arg[], char wd[]){
	char *token = strtok(arg, " ");
	token = strtok(NULL, " ");

	char buff[256], hist[256][256];
	sprintf(buff, "%s/history.txt", wd);
	FILE *fd = fopen(buff,"r");
	if(fd==NULL){
		perror("File");
	}
	if(token==NULL){
		char line[256];
		
		int i=0;
		while (fgets(line, sizeof(line), fd) != NULL) {
			strcpy(hist[i], line);
			i++;
		}
		int k;
		if(i>10){
			k = i-10;
		}
		else{
			k=0;
		}
		int cnt=0;
		for(int j=k; j<=i-1; j++){
			printf("%s", hist[j]);
			cnt++;
			if(cnt==10){
				break;
			}
		}
	}

	else{
		char line[256];
		int i=0;
		while (fgets(line, sizeof(line), fd) != NULL) {
			strcpy(hist[i], line);
			i++;
		}
		int cnt=0;
		for(int j=i-atoi(token); j<=i-1; j++){
			printf("%s", hist[j]);
		}
	}
}