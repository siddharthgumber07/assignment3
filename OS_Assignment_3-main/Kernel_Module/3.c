#include <linux/module.h>
#include <linux/kernel.h>
#include<linux/string.h>
#include <linux/sched/signal.h>


char *process=" ";

module_param(process,charp,S_IRUGO);

static int init(void){
    struct task_struct *t;    
    pr_info("!!!Entering Module!!!!\n");
    
    for_each_process(t) {
        
        if(strcmp(t->comm,process)==0){
        printk(KERN_INFO "PID       : %d",t->pid);
        printk(KERN_INFO "GID       : %d",t->cred->gid);
        printk(KERN_INFO "UID       : %d",t->cred->uid);
        printk(KERN_INFO "\n");
        //printk(KERN_INFO "Command Path     : %s",process->cdir);
           return 0; 
        }else{
            continue;
        }
         
    }
    return 0;
}

static void exit(void){
    pr_info("!!!Exiting Module!!!!\n");
    pr_info("\n");
}

MODULE_LICENSE("GPL");
module_init(init);
module_exit(exit)
