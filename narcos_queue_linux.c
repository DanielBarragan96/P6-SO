#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define CICLOS 10
#define KEY (1492)

char *pais[3]={"Peru","Bolvia","Colombia"};

// Definir una estructura que se va a usar para mandar los mensajes
typedef struct {
	long msg_type;		// Tipo de mensaje, debe ser long
	char mensaje[100];	// Contenido
	} MSGTYPE; 
	
int msgqid;


void emisor()
{
	MSGTYPE m;
	m.msg_type=1;
	strcpy(m.mensaje,"Fin");
	msgsnd(msgqid,&m,sizeof(MSGTYPE)-sizeof(long),0);
}

void receptor()
{
	MSGTYPE m;	// Donde voy a recibir el mensaje	
	msgrcv(msgqid,&m,sizeof(MSGTYPE)-sizeof(long),1,0);
	
	return;
}


void proceso(int i)
{
	int k;
	int l;
	for(k=0;k<CICLOS;k++)
	{
		receptor();
		// Entrada a la sección crítica
		printf("Entra %s",pais[i]);
		fflush(stdout);
		sleep(rand()%3);
		printf("- %s Sale\n",pais[i]);
		emisor();
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
	
	// Crear un buzón o cola de mensajes
	msgqid=msgget(0x1234,0666|IPC_CREAT);
	emisor();
	
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
		
	msgctl(msgqid,IPC_RMID,NULL);
	printf("Procesos terminados\n");
}
