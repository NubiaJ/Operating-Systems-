//Collaborator: Jasmine Makombe

#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

int randForSleep(){
  srand((time(NULL)));
  int randNum = ((rand()%5)+1);
  return randNum;
}

int randForMoney_P(){
  srand((time(NULL)*390));
  int randNum = ((rand()%100)+1);
  return randNum;
}

int randForMoney_C(){
  srand((time(NULL)*390));
  int randNum = ((rand()%50)+1);
  return randNum;
}

int main(){
  int BankAccount = 0;
  int Turn = 0;
  int balance;
  int ShmID;
  int *ShmPTR;
  
  ShmID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
  ShmPTR = (int *) shmat(ShmID, NULL, 0);
    if (*ShmPTR == -1){
      printf("*** shmat error (server) ***\n");
      exit(1);
    }
  ShmPTR[0] = BankAccount;
  ShmPTR[1] = Turn;
  
  pid_t pid;
  pid = fork();
  
  if(pid < 0)
    printf("Fork error. \n")
    
  else if (pid > 0){
    int i = 1;
    for (i = 1; i <= 25; i++){
      sleep(randForSleep());
      while (ShmPTR[1] != 0);
      if (BankAccount <= 100){
        balance = randForMoney_P();
        if (balance % 2 == 0){
          ShmPTR[0] += balance;
          printf("Dear old Dad: Deposits $%d / Balance = $%d\n", balance, ShmPTR[0]);
        }
        if (balance % 2 != 0){
          printf("Dear old Dad: Doesn't have any money to give\n")
        }
        ShmPTR[1] = 1;
      }
      else{
        printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", ShmPTR[0]);
      }
    }
    exit(0);
  }
  else {
    int i = 1;
    for (i = 1; i <= 25; i++){
      sleep(randForSleep());
      while (ShmPTR[1] != 1);
      balance = randForMoney_C();
      printf("Poor Student needs $%d\n", balance);
      if (balance <= ShmPTR[0]){
        ShmPTR[0] -= balance;
        printf("Poor Student: Withdraws $%d / Balance = $%d\n", balance, ShmPTR[0]);
      }
      if (balance > ShmPTR[0]){
        printf("Poor Student: Not Enough Cash ($%d)\n", ShmPTR[0]);
      }
      ShmPTR[1] = 0
    }
    exit(0);
  }
}














