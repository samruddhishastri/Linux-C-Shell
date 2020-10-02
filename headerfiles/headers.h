#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/wait.h>
#include<dirent.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<sys/time.h>

struct jobs{
    char name[256];
    pid_t pid;
};

int count;
struct jobs job_arr[256];

char array[256], fg_name[256], prev_directory[256];

int variable;

int kjob_pid, fg_process, shellid;