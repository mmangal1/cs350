#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int check_digit(char *optarg){
	int index = 0;
	while(optarg[index] != '\0'){
		if(!isdigit(optarg[index])){
			return 0;
		}
		index++;
	}	
	return 1;
}

int main(){
	int num_procs = atoi(argv[1]);
	if(!check_digit(num_procs)){
		fprintf(stderr, "./prog3ipc <num-procs>\n");
		exit(1);
	}

	if(num_procs < 1 || num_procs > 32){
		fprintf(stderr, ".num-procs needs to be between 1 and 32 inclusive\n");
		exit(1);
	}
		
	return 0;
}
