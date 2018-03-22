
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <sys/wait.h>


int seminit(int KEY, int val)//inicializar el semáforo con un valor
{
	int id = semget(KEY, 1, 0666 | IPC_CREAT);
	semctl(id, 0, SETVAL, val);
   return id;
}

void semwait(int id)//decrementar el semáforo.
{
	struct sembuf s;
	s.sem_num=0;
	s.sem_op=-1;	// Wait
	s.sem_flg=0;
	semop(id,&s,1);
    
	return;
}

void semsignal(int id)//incrementar el semáforo.
{
	struct sembuf s;
	s.sem_num=0;
	s.sem_op=1;	// Signal
	s.sem_flg=0;
	semop(id,&s,1);
	return;
}

