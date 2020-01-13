#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

int TAM = 4;

void handler(int sig)
{
	pid_t pid;
	pid = wait(NULL);
	printf("KERNELTYR: tlb terminado\n", pid);
}

int main(int argc, char** argv ){

	pid_t pidC;

	// printf("** proc. PID = %d comienza **\n", getpid());
	printf("KERNELTYR: PID_kerneltyr %d\n", getpid());

	//Aqui empieza el proceso hijo
	pidC = fork();
	// printf("proc. PID = %d, pidC = %d ejecutandose \n", getpid(), pidC);

	//>O Se esta ejecutando el padre
	if(pidC > 0)
	{
		printf("KERNELTYR: PID_hijo %d\n", pidC);

		//Declaramos y abrimos fichero
		FILE *fichero;
		fichero = fopen("accesos_memoria.txt", "r");

		// 1º Crear el pipe a /tmp/FIFOTLB
		// 0666 permiso de escritura
		int fd;
		mkfifo("/tmp/FIFOTLB", 0666);
		fd = open("/tmp/FIFOTLB", O_WRONLY);

		char * buffer;
		size_t tam = 0;

		while(getline(&buffer, &tam, fichero) != -1){
			write(fd, buffer, TAM);
			printf("KERNELTYR: enviado %s\n", buffer);
			sleep(1);
		}


		fclose(fichero);

		// signal(SIGCHLD, handler);
		sleep(60);
		close(fd);

		// kill(pidC, SIGUSR2);

	}

	//==0 Se esta ejecutando el hijo
	else if(pidC == 0)
	{

		char * args[] ={"./tlb", NULL};

		if(execvp(args[0], args) != 0){
			printf("No se puede ejecutar");
			return 1;
		}

	}

	//-1 Ha fallado
	else
	{
		printf("Aquí ha fallado algo");
	}



return 0;
}
