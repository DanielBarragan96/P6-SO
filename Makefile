all:
	gcc -o narcos_sem_linux narcos_sem_linux.c -lpthread

clean:

	-f narcos_sem_linux
