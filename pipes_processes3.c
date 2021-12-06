#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>


int randNumGen(){
  srand((time(NULL)*390));
  int randNum = ((rand()%1)+1);
  return randNum;
}

int main(int argc, char **argv){
  int pipefd[2];
  int pid, pid2;
  
  char *cat_args[] = {"cat", "scores", NULL};
  char *grep_args[] = {"grep", "-i", argv[0], "scores", NULL};
  char *sort_args[] = {"sort", "scores", NULL};
  
  pipe(pipefd);
  pid = fork();
  
  if (pid == 0){
    dup2(pipefd[0], 0);
    close(pipefd[1]);
    execvp("grep", grep_args);
  }
  else{
    pid2 = fork();
    if (pid2 == 0){
      sleep(randNumGen());
      dup2(pipefd[1], 1);
      close(pipefd[0]);
      execvp("sort", sort_args);
    }
    dup2(pipefd[1], 1);
    close(pipefd[0]);
    execvp("cat", cat_args);
  }
}