#include"headerfiles/headers.h"
#include"headerfiles/prompt.h"
#include"headerfiles/takeinput.h"
#include"headerfiles/bg_signal.h"

int main(){
	count=0;
	char cwd[256];
	getcwd(cwd, sizeof(cwd));
	shellid = getpid();
	strcpy(array, cwd);

	printf("\n\n\n");
	
	prev_directory[0] = '\0';
	fg_process = -1;

	while(1){
		signal(SIGINT, interrupt_signal);
		signal(SIGCHLD, bg_signal);
		signal(SIGTSTP, stop_signal);
		//printf("123\n");
		prompt(cwd);
		//printf("456\n");
		takeinput(cwd);
		//printf("789\n");
	}
}