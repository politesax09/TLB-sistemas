#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

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
		int fd;
		char buffer[] = "msg 1 ...";
		// 1º Crear el pipe a /tmp/FIFOTLB
		// 0666 permiso de escritura
		mkfifo("/tmp/FIFOTLB", 0666);
		fd = open("/tmp/FIFOTLB", O_WRONLY);

		gets(buffer);


		write(fd, buffer, sizeof(buffer));

		sleep(2);
		close(fd);
	}

	//==0 Se esta ejecutando el hijo
	else if(pidC == 0)
	{
		execv("./tlb", NULL);

		printf("HIJO: PID_hijo %d\n", getpid());
	}

	//-1 Ha fallado
	else
	{
		printf("Aquí ha fallado algo");
	}



return 0;
}
