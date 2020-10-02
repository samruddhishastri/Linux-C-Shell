#include"headerfiles/headers.h"
#include"headerfiles/man.h"
#include"headerfiles/system_process.h"

void man(){
	char token[30];
	strcpy(token, "cat README.txt");
	int i=0, k=0;
    char name[256];

    while(token[i]!='\0'){
        name[k] = token[i];
        i++;
        k++;
   	}
    name[k] = '\0';
    system_process(name); 
}