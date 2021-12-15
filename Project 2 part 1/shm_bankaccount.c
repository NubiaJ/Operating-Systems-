//Collaborators: Jasmine Makombe, Gerone Hamilton

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/shm.h> 
#include <time.h>

int randForSleep(){
  srand ((time(NULL)));
  int randNum = ((rand()%5)+1);
  return randNum;
}

int randForMoney_100(){
  srand((time(NULL)*390));
  int randNum = ((rand()%100)+1);
  return randNum;
}

int randForMoney_50(){
  srand((time(NULL)*390));
  int randNum = ((rand()%50)+1);
  return randNum;
}

void ChildProcess(int BankShm[], sem_t *mutex){
  int i, sleep_num, rand_num, need;
  int localBalance = 0;
  
  for(i = 1; i <=25; i++){
    sleep_num = randForSleep();
    sleep(sleep_num);
    printf("Poor Student: Attempting to Check Balance\n");
    rand_num = randForMoney_100;
    if (rand_num % 2 == 0){
      sem_wait(mutex);
      localBalance = BankShm[0];
      need = randForMoney_50();
      printf("The child needs %d\n", need);
      printf("Poor Student needs $%d\n", need);
      if (need <= localBalance){
        BankShm[0] = BankShm[0] - need;
        printf("Poor Student: Withdraws $%d / Balance = $%d\n", need, localBalance);
      }
      else{
        printf("Poor Student: Not Enough Cash (%d)\n", localBalance);
      }
      localBalance = BankShm[0];
      sem_post(mutex);
      sleep(2);
    }
    else{
      printf("Poor Student: Last Checking Balance = %d\n", localBalance);
    }
  }
  sleep(2);
  exit(0);
}

void ParentProcesses(int BankShm[], sem_t *mutex){
  int i, sleep_num, rand_num, amount;
  int localBalance = 0;
  printf("My bank account balance is %d\n", BankShm[0]);
  printf("My local balance is %d\n", localBalance);
  
  for (i = 1; i <= 25; i++){
    sleep_num = randForSleep();
    sleep(sleep_num);
    printf("Dear Old Dad: Attempting to check balance\n");
    rand_num = randForMoney_100();
    if (rand_num % 2 == 0 && localBalance < 100){
      sem_wait(mutex);
      localBalance = BankShm[0];
      printf("*****Dear Old Dad: Bank account balance is now $%d\n", BankShm[0]);
      amount = randForMoney_100();
      printf("The amount in Parent is %d\n", amount);
      if (amount % 2 == 0){
        BankShm[0] = BankShm[0] + amount;
        localBalance = BankShm[0];
        printf("Dear Old Dad: Deposits $%d / Balance = %d\n", amount, localBalance);
      }
      else{
        printf("Dead Old Dad: Think Student has enough Cash = (%d)\n", localBalance);
      }
      sem_post(mutex);
      sleep(2);
    }
    else{
      printf("Dear old Dad: Last Checking Balance = %d\n", localBalance);
    }
  }
  printf("Dear old Dad: %d has completed.\n", getpid());
  printf("*** Dear old Dad process is done ***\n");
}


void main(void){
  int ShmID;
  int *ShmPTR;
  sem_t* mutex;
  
  if ((mutex = sem_open("examplesemaphore", O_CREAT, 0644, 1)) == SEM_FAILED){
    perror("semaphore initialization");
    exit(1);
  }
  
  ShmID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
  if (ShmID < 0){
    printf("*** BankAccount error (parent) ***\n");
    exit(1);
  }
  printf("Parent has recieved one integer of shared memory...\n");
  
  ShmPTR = (int *) shmat(ShmID, NULL, 0);
  if (*ShmPTR == -1){
    printf("***shmat error (server) ***\n");
    exit(1);
  }
  printf("Server has attached the shared memory...\n");
  
  ShmPTR[0] = 0;
  
  pid_t pid;
  pid = fork();
  
  if (pid < 0){
    printf("Fork error.\n");
  }
  
  if (pid == 0){
    ChildProcess(ShmPTR, mutex);
  }
  else{
    ParentProcesses(ShmPTR, mutex);
  }
}








































