#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int TAM = 4;
int tiempoglobal=0;
int numfallos=0;
#define MAX_LINE 100

	typedef struct {
	short int pagina;
	short int marco;
	short int valida;
	int tiempo;	
} T_TLB;

void printTLB(T_TLB *TLB){
	
	int i=0;
	
	for(i=0; i<TAM ; i++){
		printf("| p:%d | m:%d | v:%d | t:%d |\n", TLB[i].pagina, TLB[i].marco, TLB[i].valida, TLB[i].tiempo);
	}

	}

int main(){
	int i=0;
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
	
	fd = open("/tmp/FIFOTLB", O_RDONLY);
	
	while(read(fd, buffer, MAX_LINE)){
		printf("%s\n",buffer);
		tiempoglobal++;
	}
	
	
		
	printf("%d",tiempoglobal);
	
	
	close(fd);





return 0;
}
