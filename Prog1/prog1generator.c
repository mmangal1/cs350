#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "getArgs.h"

/*int check_digit(char* optarg){
	int index = 0;
	while(optarg[index] != '\0'){
		if(!isdigit(optarg[index])){
			return 0;
		}
		index++;
	}	
	return 1;
}*/

int main(int argc, char *argv[]){
	/*int option = 0;
	int flag = 0;
	int num_int = 100;
	int min_int = 1;
	int max_int = 255;
	char *f_out = NULL;
	unsigned long seed = 0;
	char *p;*/
	struct arguments *gen;
	gen = get_args(argc, argv);

	//generating num_int random numbers from range min_int to max_int
	srand(gen->seed);

	if(gen->out_flag){
		FILE* fp = fopen(gen->f_out, "w");
		int r_num;
		fprintf(fp, "%d\n", gen->num_int);
		for(int x = 0; x < gen->num_int; x++){
			r_num = ((rand()%(gen->max_int + 1 - gen->min_int)) +gen->min_int);
			fprintf(fp, "%d\n", r_num);
		}
		fclose(fp);
	}else{
		printf("%d\n", gen->num_int);
		for(int x = 0; x < gen->num_int; x++){
			printf("%d\n", ((rand()%(gen->max_int + 1 - gen->min_int)) + gen->min_int));
		}
	}


/*	printf("num_int%d\n", gen->num_int);
	printf("min_int%d\n", gen->min_int);
	printf("max_int%d\n", gen->max_int);
*/
	free(gen);	
	return 0;
}
