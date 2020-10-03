#include"headerfiles/headers.h"
#include"headerfiles/ls.h"

void longlist_hidden(char a[], char wd[]){

	DIR *dir;
    struct dirent *fil;
    struct stat thestat;
    struct passwd *tf; 
    struct group *gf;

    char buf[512];

    dir = opendir(a);

    if(dir==NULL){
    	printf("%d\n", errno);
    	perror("Directory:");
    	return;
    }

    printf("\033[1;32m%s\033[0m;\n", a);

    while((fil = readdir(dir)) != NULL) {

        sprintf(buf, "%s/%s", a, fil->d_name);
        stat(buf, &thestat);

        mode_t p = thestat.st_mode;

        printf( (S_ISREG(p)) ? "-" : "d");
        printf( (p & S_IRUSR) ? "r" : "-");
        printf( (p & S_IWUSR) ? "w" : "-");
        printf( (p & S_IXUSR) ? "x" : "-");
        printf( (p & S_IRGRP) ? "r" : "-");
        printf( (p & S_IWGRP) ? "w" : "-");
        printf( (p & S_IXGRP) ? "x" : "-");
        printf( (p & S_IROTH) ? "r" : "-");
        printf( (p & S_IWOTH) ? "w" : "-");
        printf( (p & S_IXOTH) ? "x" : "-");

        printf(" ");

        printf("%ld ", thestat.st_nlink);

        tf = getpwuid(thestat.st_uid);
        printf("%s ", tf->pw_name);

        gf = getgrgid(thestat.st_gid);
        printf("%7s ", gf->gr_name);

        printf("%7zu",thestat.st_size);

        char *time = (char *)malloc(sizeof(char) * 50); 
        strftime(time, 50, "%b  %d %H:%M", localtime( &thestat.st_mtime));

        printf(" %7s", time);

        if(S_ISREG(p)){
            printf(" %s\n", fil->d_name);
        }
        else{
            printf("\033[1;36m %s\n", fil->d_name);
            printf("\033[0m");  
        }

    }

    closedir(dir);
}

void longlist(char a[], char wd[]){
	DIR *dir;
    struct dirent *fil;
    struct stat thestat;
    struct passwd *tf; 
    struct group *gf;

    char buf[512];

   	dir = opendir(a);

    if(dir==NULL){
    	printf("%d\n", errno);
    	perror("Directory:");
    	return;
    }

     printf("%s\n", a);

    while((fil = readdir(dir)) != NULL) {

    	if(strcmp(fil->d_name, ".")==0 || strcmp(fil->d_name, "..")==0){
    		continue;
    	}

        sprintf(buf, "%s/%s", a, fil->d_name);
        stat(buf, &thestat);

        mode_t p = thestat.st_mode;

        printf( (S_ISREG(p)) ? "-" : "d");
        printf( (p & S_IRUSR) ? "r" : "-");
        printf( (p & S_IWUSR) ? "w" : "-");
        printf( (p & S_IXUSR) ? "x" : "-");
        printf( (p & S_IRGRP) ? "r" : "-");
        printf( (p & S_IWGRP) ? "w" : "-");
        printf( (p & S_IXGRP) ? "x" : "-");
        printf( (p & S_IROTH) ? "r" : "-");
        printf( (p & S_IWOTH) ? "w" : "-");
        printf( (p & S_IXOTH) ? "x" : "-");

        printf(" ");

        printf("%ld ", thestat.st_nlink);

        tf = getpwuid(thestat.st_uid);
        printf("%s ", tf->pw_name);

        gf = getgrgid(thestat.st_gid);
        printf("%7s ", gf->gr_name);

        printf("%7zu",thestat.st_size);

        char *time = (char *)malloc(sizeof(char) * 50); 
        strftime(time, 50, "%b  %d %H:%M", localtime( &thestat.st_mtime));

        printf(" %7s", time);

        if(S_ISREG(p)){
            printf(" %s\n", fil->d_name);
        }
        else{
            printf("\033[1;36m %s\n", fil->d_name);
            printf("\033[0m");  
        }


    }
    closedir(dir);
}

void hidden(char a[], char wd[]){
	DIR *dir;
    struct dirent *fil;
    struct stat thestat;
    char buf[512];
    dir = opendir(a);

    if(dir==NULL){
    	printf("%d\n", errno);
    	perror("Directory:");
    	return;
    }

     printf("%s\n", a);
    while((fil = readdir(dir)) != NULL) {

        sprintf(buf, "%s/%s", a, fil->d_name);
        stat(buf, &thestat);
        mode_t p = thestat.st_mode;
        if(S_ISREG(p)){
        	printf("%s\n", fil->d_name);
    	}
    	else{
    		printf("\033[1;36m%s\n", fil->d_name);
        	printf("\033[0m");	
    	}
    }

    closedir(dir);
}

void list(char a[], char wd[]){

	DIR *dir;
    struct dirent *fil;
    struct stat thestat;
    char buf[512];

    dir = opendir(a);

    if(dir==NULL){
    	printf("%d\n", errno);
    	perror("Directory:");
    	return;
    }

     printf("%s\n", a);
    while((fil = readdir(dir)) != NULL) {
    	

    	if(strcmp(fil->d_name, ".")==0 || strcmp(fil->d_name, "..")==0){
    		continue;
    	}
        
        sprintf(buf, "%s/%s", a, fil->d_name);
        stat(buf, &thestat);
        mode_t p = thestat.st_mode;

        if(S_ISREG(p)){
        	printf("%s\n", fil->d_name);
    	}
    	else{
    		printf("\033[1;36m%s\n", fil->d_name);
        	printf("\033[0m");	
    	}
    }

    closedir(dir);
}

void ls(char arg[], char wd[]){

	char *token = strtok(arg, " ");
	char c[256][256], d[256][256]; 
	char cwd[256];

	token = strtok(NULL, " ");

	int x=0, y=0;
	
	while(token!=NULL){
		if((strcmp(token,"-l")==0) || (strcmp(token,"-al")==0) || (strcmp(token,"-la")==0) || (strcmp(token, "-a")==0)){
			strcpy(c[x], token);
			x++;	
		}
		else{

			if(strcmp(token, "~")==0){
				strcpy(d[y], wd);
			}

			else{
				strcpy(d[y], token);
			}

			y++;
		}
		token = strtok(NULL, " ");
	}

	int l = 0, h = 0;
		
	for(int i=0; i<x; i++){
		if(strcmp(c[i], "-l")==0){
			l = 1;
		}
		if(strcmp(c[i], "-a")==0){
			h = 1;
		}
		if((strcmp(c[i], "-al")==0) || (strcmp(c[i], "-la")==0)){
			l = 1, h = 1;
		}
	}

	if(y==0){
		getcwd(cwd, sizeof(cwd));
		strcpy(d[0], cwd);
		y++;
	}


	for(int i=0; i<y; i++){
        
		if(l==0 && h==0){
			list(d[i], wd);
		}
		else if(l==1 && h==0){
			longlist(d[i], wd);
		}
		else if(l==0 && h==1){
			hidden(d[i], wd);
		}
		else{
			longlist_hidden(d[i], wd);
		}
	}

}