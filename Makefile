all:
	gcc -o narcos_sem_linux narcos_sem_linux.c -lpthread
	gcc -o narcos_queue_linux narcos_queue_linux.c -lpthread

clean:

	-f narcos_sem_linux
	-f narcos_queue_linux
