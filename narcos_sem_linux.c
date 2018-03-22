#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <sys/wait.h>

#define CICLOS 10
#define KEY (1492)

char *pais[3]={"Peru","Bolvia","Colombia"};
int *g;
sem_t mutex;

void proceso(int i)
{
	int k;
	int l;
	for(k=0;k<CICLOS;k++)
	{
		sem_wait (&mutex);
		// Entrada a la sección crítica
		printf("Entra %s",pais[i]);
		fflush(stdout);
		sleep(rand()%3);
		printf("- %s Sale\n",pais[i]);
		sem_post (&mutex);
		// Salida de la sección crítica
		// Espera aleatoria fuera de la sección crítica
		sleep(rand()%3);
	}
	exit(0);
// Termina el proceso
}

int main()
{
	//http://www.minek.com/files/unix_examples/semab.html
	/*
	int id = semget(KEY, 1, 0666 | IPC_CREAT);
	if  (id<0) 
	{
		perror("Semaphore creation failed  Reason:");
	}
	if( semctl(id, 0, SETVAL, argument) < 0)
    {
       fprintf( stderr, "Cannot set semaphore value.\n");
    }
    else
    {
       fprintf(stderr, "Semaphore %d initialized.\n", KEY);
    }
    */
    
     sem_init(&mutex, 0, 1);
     
    int pid;
	int status;
	int args[3];
	int i;
	srand(getpid());
	for(i=0;i<3;i++)
	{
		// Crea un nuevo proceso hijo que ejecuta la función proceso()
		pid=fork();
		if(pid==0)
		proceso(i);
	}
	for(i=0;i<3;i++)
		pid = wait(&status);
}
