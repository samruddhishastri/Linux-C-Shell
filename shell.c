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

	while(1){
		fg_process = -1;
		signal(SIGCHLD, bg_signal);
		signal(SIGINT, interrupt_signal);
		signal(SIGTSTP, stop_signal);
		prompt(cwd);
		takeinput(cwd);
	}


}
