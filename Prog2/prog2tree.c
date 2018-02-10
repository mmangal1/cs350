#include <stdlib.h>
#include <getopt.h>
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


int main(int argc, char *argv[]){
	
	int option;
	int num_levels, num_children, sleep_time;
	num_levels = num_children = sleep_time = 1;
	
	while((option = getopt(argc, argv, ":uN:M:ps:")) != -1){
		switch(option){
			case 'u':
				fprintf(stderr, "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]\n");
				exit(1);
			case 'N':
				if(check_digit(optarg)){
					
				}
		}
	}
}
