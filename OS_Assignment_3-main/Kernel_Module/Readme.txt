Firstly, defined a character pointer(*process) for storing the process name inputed by user on terminal.

Then, taking input via module_param() on terminal for process name.

Then, looping over all the processes by using for_each_process() which takes a pointer of task_struct i.e. *t.

Now, comparing the process name and printing the PID, Group ID, User ID, Process path respectively by using task_struct pointer(t).

t->pid		:	gives process ID
t->gid		:	gives Group ID
t->uid		:	gives User ID
process->cdir   :	giver process path

init() runs for entring in kernel module.

exit() runs for exiting from kernel module.
					
