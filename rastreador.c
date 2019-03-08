#include <unistd.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

#define opcion_rastreador1 "-V"
#define opcion_rastreador2 "-v"
#define MAX_ARGS 10

char* PROG;
char* PROG_ARGS[MAX_ARGS];
int argument_count = 0;

void set_up_args_array();
void copy_args_starting_from(char* array1[], char* array2[], int init_pos);
void set_null_pointer_at_end(char* array[]);
void print_arguments(char* array[]);

int main(int argc, char *argv[]){

	printf("La cantidad de argumentos son: %d\n", argc);

	for(int i = 0; i < argc; i++){
		printf("\nArgumento: %s\n", argv[i]);
	}

	argument_count = argc;
	set_up_args_array();

	if((argv[1] != opcion_rastreador1) && (argv[1] != opcion_rastreador2)){

		PROG = argv[1];
		PROG_ARGS[0] = PROG;
		printf("\nEl programa a ejecutar es %s\n", PROG);

		// Prog has arguments
		if(argc > 2){
			copy_args_starting_from(PROG_ARGS, argv, 2);
		}

		set_null_pointer_at_end(PROG_ARGS);

	}

	printf("\nLa lista de argumentos de %s son:\n", PROG);
	print_arguments(PROG_ARGS);
	printf("-------EJECUCION DEL OTRO PROGRAMA--------\n");
	execvp(PROG, PROG_ARGS);

	return 0;
}

void set_up_args_array(){
	for(int i = 1; i < MAX_ARGS; i++){
		PROG_ARGS[i] = "";
	}
}

// Take elements from array2 starting from init_pos and copy them to array1
void copy_args_starting_from(char* array1[], char* array2[], int init_pos){
	for(int index = 1; init_pos < argument_count; index++){
		array1[index] = array2[init_pos];
		init_pos++;
	}
}

void set_null_pointer_at_end(char* array[]){
	int index = 0;
	while (array[index] != "") {
		index++;
	}
	array[index] = NULL;
}

void print_arguments(char* array[]){
	for(int index = 0; array[index] != ""; index++){
		printf("\n->%s\n", array[index]);
	}
	printf("\n");
}
