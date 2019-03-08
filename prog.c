#include <unistd.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	
	printf("\nSoy el otro programa\n");
	
	printf("\nLa cantidad de argumentos son: %d\n", argc);
	
	for(int i = 0; i < argc; i++){
		printf("\nArgumento: %s\n", argv[i]);
	}
	
	return 0;
}
