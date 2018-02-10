#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include "getArgs.h"

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


struct arguments* get_args(int argc, char *argv[]){
	struct arguments *arg;
	arg = (struct arguments *) malloc(sizeof(struct arguments));
	if(arg == NULL){
		perror("Error in creating memory for arg : ");
		exit(1);
	}
	arg->in_flag = 0;
	arg->seed_flag = 0;
	arg->out_flag = 0;
	arg->count_flag = 0;
	arg->num_int = 100;
	arg->min_int = 1;
	arg->max_int = 255;
	arg->f_out = NULL;
	arg->f_count = NULL;
	arg->f_in = NULL;
	arg->host = NULL;
	arg->seed = 0;
	int option = 0;

	char* p;
	if(strcmp(argv[0], "./prog1generator") == 0){
		for(int x = 1; x < argc; x++){
			if(strcmp("-u", argv[x]) == 0){
				fprintf(stderr, "ussage: prog1generator [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>] \n");
				free(arg);
				exit(1);
				
			}
		}
		while((option = getopt(argc, argv, ":un:m:M:s:o:")) != -1){
			switch(option){
				case 'u' : 
					fprintf(stderr, "ussage: prog1generator [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>] \n");
					free(arg);
					exit(1);
					break;
				case 'n' :
					if(check_digit(optarg)){
						arg->num_int = atoi(optarg);
						if(arg->num_int < 0 || arg->num_int > 1000000){
							fprintf(stderr, "num-integers is out of range, provide between 0 and 1000000\n");
							free(arg);
							exit(1);
						}
					}else{
						fprintf(stderr, "num_int needs to be between 0 and 1000000\n");
						free(arg);
						exit(1);
		
					}
					break;
				case 'm' :
					if(check_digit(optarg)){
						arg->min_int = atoi(optarg);
						if(arg->min_int < 1){
							fprintf(stderr, "min-int should be greater or equal to 1\n");
							free(arg);
							exit(1);
						}
					}else{
						fprintf(stderr, "min_int needs to be greater or equal to 1\n");
						free(arg);
						exit(1);
					}
					break;
				case 'M' :
					if(check_digit(optarg)){
						arg->max_int = atoi(optarg);
						if(arg->max_int > 1000000){
							fprintf(stderr, "max_int should be in between 2 and 1000000\n");
							free(arg);
							exit(1);
						}
					}else{
						fprintf(stderr, "max_int needs to be greater or equal to 1\n");
						free(arg);
						exit(1);
					}
					break;
				case 'o' :
					arg->f_out = optarg;
					arg->out_flag = 1;	
					break;
				case 's' :
					arg->seed_flag = 1;
					arg->seed = strtoul(optarg, &p, 10);
					break;
				case '?' :
					fprintf(stderr, "invalid option provided\n");
					free(arg);
					exit(1);	
			}
		}
	} else if(strcmp(argv[0], "./prog1sorter") == 0){
		for(int x = 1; x < argc; x++){
			if(strcmp("-u", argv[x]) == 0){
				fprintf(stderr, "ussage: prog1sorter [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>] \n");
				free(arg);
				exit(1);
				
			}
		}
		
		while((option = getopt(argc, argv, ":un:m:M:i:o:c:")) != -1){
			switch(option){
				case 'u' : 
					fprintf(stderr, "ussage: prog1sorter [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>] \n");
					free(arg);
					exit(1);
					break;
				case 'n' :
					if(check_digit(optarg)){
						arg->num_int = atoi(optarg);
						if(arg->num_int < 0 || arg->num_int > 1000000){
							fprintf(stderr, "num-integers is out of range, provide between 0 and 1000000\n");
							free(arg);
							exit(1);
						}
					}else{
						fprintf(stderr, "num_int needs to be between 0 and 1000000\n");
						free(arg);
						exit(1);
		
					}
					break;
				case 'm' :
					if(check_digit(optarg)){
						arg->min_int = atoi(optarg);
						if(arg->min_int < 1){
							fprintf(stderr, "min-int should be greater or equal to 1\n");
							free(arg);
							exit(1);
						}
					}else{
						fprintf(stderr, "min-int should be greater or equal to 1\n");
						free(arg);
						exit(1);

					}
					break;
				case 'M' :
					if(check_digit(optarg)){
						arg->max_int = atoi(optarg);
						if(arg->max_int > 1000000){
							fprintf(stderr, "max_int should be in between 2 and 1000000\n");
							free(arg);
							exit(1);
						}
					}else{
						fprintf(stderr, "max_int should be in between 2 and 1000000\n");
						free(arg);
						exit(1);
						
					}
					break;
				case 'i' : 
					arg->f_in = optarg;
					arg->in_flag = 1;
					break;	
				case 'o' :
					arg->f_out = optarg;
					arg->out_flag = 1;	
					break;
				case 'c' :
					arg->f_count = optarg;
					arg->count_flag = 1;
					break;
				case '?' :
					fprintf(stderr, "invalid option provided\n");
					free(arg);
					exit(1);	
			}
		}	
	}
	return arg;
}
