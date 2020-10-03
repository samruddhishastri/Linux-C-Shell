Run the Shell:

1. Run the command 'make' followed by ./a.out
2. A prompt will be displayed.
3. Enter the commands into the shell and hit ENTER.
4. to exit from the shell, enter 'quit' and hit ENTER.


Features:

* Handled redirection, piping, ctrl+C, ctrl+Z, 

1. cd:

Syntax: cd [path]

Description: 
Change the current working directory to the directory specified in the path.
Error is displayed if no such path exists.
Can handle arguments [.], [..], [-] and [~].
Current working directory is displayed in the prompt.
Displays the absolute path of the shell when the present working directory is home (wrt shell) and path entered is [..].

Files: cd.c, cd.h 



2. pwd:

Syntax: pwd

Description: 
Prints the present working directory with respect to the shell.

Files: pwd.c, pwd.h



3. echo:

Syntax: echo [arguments]

Description: 
Prints the arguments.
Multiline strings, environment variables, and quotes are not handeled.

Files: echo.c, echo.h



4. ls:

Syntax: ls [arguments]

Description: 
Lists the directory contents of the path specified in arguments.
If the arguments is NULL, then directory contents of present working directory are displayed
If the path does not exist error is displayed
Can handle flags [-l], [-a], [-al]/[-la]

Files: ls.c, ls.h



5. system process:

Syntax: <command> [arguments]

Descritpion:
Runs the basic system process.
Can handle flag [&] for background processes
If process does not exist error is displayed

Files: system_process.c, system_process.h


6. pinfo:

Syntax: pinfo [pid]

Descritpion:
Displays pid, process status, memory and executable path of the process with pid entered.
If pid is NULL the details of process related to shell is displayed.
If no process exists with the pid given, error is displayed.

Files: pinfo.c, pinfo.h



7. finished background process

Syntax: No syntax

Description:
Whenever a background process exits, its exit details are diaplyed.

Files: bg_exit.c, bg_exit.h 



8. nightswatch

Syntax: nightswatch -n [time] <command>
Description:
Runs <command> and displays the output every [time] seconds.
The commands that can be run are interrupt or newborn.
Interrupt displays the number of times each CPU was interrupted.
Newborn displays the most recently created process.
If command is not running, error is displayed. 
On pressing q, it does not exit.

Files: nightswatch.c, nightswatch.h



9. history

Syntax: history [arguments]

Description:
Displays the last [argumnets] number of commands entered into the shell.
At max, only last 20 commands can be traced.
If [arguments] is NULL, last few commands, at max 10, are displayed.
If the file 'history.txt', is not created or is unable to access error is displayed.

Files: history.c, history.h

10. man

Syntax: man

Description:
Displays information and functionalities of shell

Files: man.c, man.h

11. setenv

Syntax: setenv var [value]

Description:
Creates an environment variable var with the given value. If an environment variable var already exists, it updates its value to 'value'

Files: env_var.c, env_var.h

12. unsetenv

Syntax: unsetenv var

Description:
Deletes an environment variable var.

Files: env_var.c, env_var.h

13. jobs

Syntax: jobs

Description:
Displays all the current background processes.

Files: show_jobs.c, show_jobs.h

14. kjob

Syntax: kjob [job_number] [signal_number]

Description:
Sends the signal with the signal number to the background process with the given job number.

Files: kjob.c, kjob.h

15. fg

Syntax: fg [job_number]

Description: Brings the running or stopped background job corresponding to ​job number​ to the foreground, and changes its state to running​

Files: fg_bg.c, fg_bg.h

16. bg

Syntax: bg [job_number]

Description: Changes the state of a stopped background job to running (in the background).

Files: fg_bg.c, fg_bg.h

17. overkill

Syntax: overkill

Description: Kills all the background processes.

Files: overkill.c, overkill.h

Other files:

headers.h: Contains all the headers of imported C libraries
history.txt: Stores history of commands entered into the shell
makefile: Contains compilation command of shell
prompt.c: Code for prompt
prompt.h: headerfile for prompt
README.txt: displays basic information about shell
shell.c: contains main loop
takeinput.c: Code for taking input from the users and parseing it. Redirection and piping also implemented.
takeinput.h: headerfile for input
a.out: executable of the shell
bg_signal.c: Signal handling implemented
bg_signal.h: headerfile for signal handling