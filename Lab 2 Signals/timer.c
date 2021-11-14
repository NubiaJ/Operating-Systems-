#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int flip = 1;
int i = 0;

void handler(int signum){
  printf("1 \n");
  alarm(1);
  i += 1;
  flip = 0;
}

void inthandler(int sig_Num){
  signal(SIGINT, inthandler);
  printf("Alarm number = %d \n", i);
  exit(0);
}

int main(int argc, char * argv[]){
  for (;;){
    signal(SIGALRM, handler);
    alarm(1);
    while(flip);
      printf("2 \n");
      signal(SIGINT, inthandler);
      flip = 1;
  }
  return 0;
}
