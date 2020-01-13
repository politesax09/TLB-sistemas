#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TAM 4
#define MAX_LINE 100
int tiempoglobal=0;
int numfallos=0;

typedef struct {
short int pagina;
short int marco;
short int valida;
int tiempo;
} T_TLB;

void printTLB(T_TLB *TLB){
	int i = 0;

	for(i = 0; i < TAM ; i++){
		printf("| p:%d | m:%d | v:%d | t:%d |\n", TLB[i].pagina, TLB[i].marco, TLB[i].valida, TLB[i].tiempo);
	}

}

// Inicializar pipe
int init_pipe(int* pipe) {
    if (*pipe = open("/tmp/FIFOTLB", O_RDONLY) < 0) {
        return -1;
    }
    printf("pipe:%d\n", *pipe);
    return 0;
}

// Casting a hexadecimal
// int hex_cast(char* buffer) {
//     int num = (int)strtol(buffer, NULL, 16);
//     return num;
// }

int main(){
	int i = 0;
	T_TLB TLB[TAM];

	for(i=0; i<TAM ; i++){
		TLB[i].valida=0;
		TLB[i].tiempo=0;
		TLB[i].pagina=255;
		TLB[i].marco=((2+i)%4);
	}

	printTLB(TLB);

	//Otra parte del pipe
	int fd;
	char buffer[MAX_LINE];

	// fd = open("/tmp/FIFOTLB", O_RDONLY);

	if (init_pipe(&fd) < 0)
		printf("TLB: ERROR: No se puede abrir FIFOTLB\n");
	printf("TLB: fd: %d\n", fd);

	while(read(fd, buffer, MAX_LINE)){
		printf("TLB: %s\n",buffer);

		tiempoglobal++;
		sleep(2);
	}
	printf("TLB: %d",tiempoglobal);

	close(fd);
	printf("TLB: He terminao\n");
	// kill(getppid(), SIGCHLD);

return 0;
}
