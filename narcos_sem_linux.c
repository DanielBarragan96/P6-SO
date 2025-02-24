#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include "semaphores.h"

#define CICLOS 10
#define KEY (1492)

char *pais[3]={"Peru","Bolvia","Colombia"};
int mutex;

void proceso(int i)
{
	int k;
	int l;
	for(k=0;k<CICLOS;k++)
	{
		semwait (mutex);
		// Entrada a la sección crítica
		printf("Entra %s",pais[i]);
		fflush(stdout);
		sleep(rand()%3);
		printf("- %s Sale\n",pais[i]);
		semsignal (mutex);
		// Salida de la sección crítica
		// Espera aleatoria fuera de la sección crítica
		sleep(rand()%3);
	}
	exit(0);// Termina el proceso
}

int main()
{   
    int pid;
	int status;
	int args[3];
	int i;
	srand(getpid());
	
	mutex = seminit(KEY, 0);
	semsignal (mutex);
	
	for(i=0;i<3;i++)
	{
		// Crea un nuevo proceso hijo que ejecuta la función proceso()
		pid=fork();

		if(pid==0)
		{
			proceso(i);
		}
	}
	for(i=0;i<3;i++)
		pid = wait(&status);
	semctl(mutex,0,IPC_RMID,0);
	printf("Procesos terminados\n");
}
