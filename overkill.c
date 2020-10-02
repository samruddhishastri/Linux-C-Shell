#include"headerfiles/headers.h"
#include"headerfiles/overkill.h"

void overkill(){
	for(int i=1; i<=count; i++){
		kill(job_arr[i].pid, SIGKILL);
	}
}