#include  <stdio.h>
#include  <sys/types.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <time.h>

#define   MAX_COUNT  200

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

int randProcess(){
  srand((time(NULL)*390));
  int randNum = ((rand()%30)+1);
  return randNum;
}

int randSleep(){
  srand((time(NULL)));
  int randNum = ((rand()%10)+1);
  return randNum;
}


void  main(void)
{
     pid_t  pid1, pid2;

     pid1 = fork();
     if (pid1 == 0) {
          ChildProcess();
     }
     else {
       pid2 = fork();
       if (pid2 == 0){
         ChildProcess();
       }
     }
          ParentProcess(); 
}

void  ChildProcess(void)
{
     int   i;

     for (i = 1; i <= randProcess(); i++){
          printf("Child Pid: %d is going to sleep!\n", getpid());
          sleep(randSleep());
          printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
}
exit(0);
}

void  ParentProcess(void)
{
     wait(NULL);
     int   i;

     //for (i = 1; i <= MAX_COUNT; i++)
          printf("Child Pid: %d has completed\n", getpid());
     //printf("*** Parent is done ***\n");
}