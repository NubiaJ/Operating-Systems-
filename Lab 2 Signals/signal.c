/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int flip = 1;

void handler(int signum)
{ //signal handler
  flip = 1;
  printf("Hello World!\n");
  alarm(1);
  flip = 0;
  //exit(1); //exit after printing
}

int main(int argc, char * argv[])
{
  for (;;){
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  alarm(1); //Schedule a SIGALRM for 1 second
  while(flip); //busy wait for signal to be delivered
    printf("Turing was right!\n");
    flip = 1;
  }
  return 0; //never reached
}
