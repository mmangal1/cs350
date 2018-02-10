#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>
#include "getArgs.h"
#include "timeval.h"

int cmpfunc(const void *a, const void *b){
	return ( *(int*)a - *(int*)b );
}


int count_freq(int* array, int size, int num){
	int count = 0;
	for(int x = 0; x < size; x++){
		if(array[x] == num){
			count++;
		}
	}
	return count;
}

int main(int argc, char *argv[]){
	
	char* host;
	host = getenv("USER");
/*	int option = 0;
	int in_flag = 0;
	int out_flag = 0;
	int count_flag = 0;
	int num_int = 100;
	int min_int = 1;
	int max_int = 255;
	char *f_out = NULL;
	char *f_count = NULL;
	char *f_in = NULL;
*/

	struct arguments *gen;
	gen = get_args(argc, argv);
	
	struct timeval start, end, result;


	get_time(&start);
	
	int *nums;

	//take in input
	if(gen->in_flag){
		FILE *input_fp = fopen(gen->f_in, "r");
		char str[1024];
		if(input_fp == NULL){
			fprintf(stderr, "invalid input file provided\n");
			free(gen);
			fclose(input_fp);
			exit(1);
		}
		fgets(str, 1024, input_fp);
		if(atoi(str) != gen->num_int){
			fprintf(stderr, "The num_int given and num_int inside input file is not the same\n");
			free(gen);
			exit(1);
		}
		nums = (int *)malloc(gen->num_int*sizeof(int));
		if(nums == NULL){
			perror("Memory for array cannot be allocated : ");
			free(gen);
			fclose(input_fp);
			exit(1);
		}
		int index = 0;
		int counter = 0;
		while(fgets(str, 1024, input_fp)!=NULL){
			if(atoi(str) < gen->min_int || atoi(str) > gen->max_int){
				fprintf(stderr, "generated number %d is out of range\n", atoi(str));
				free(nums);
				free(gen);
				fclose(input_fp);
				exit(1);
			}
			counter++;
			nums[index] = atoi(str);
			index++;
		}
		if(counter < gen->num_int || counter > gen->num_int){
			fprintf(stderr, "Number of values given is not the same as num_int\n");
			free(nums);
			free(gen);
			fclose(input_fp);
			exit(1);
			
		}
		fclose(input_fp);
	}else{
		char number_count[1024];
		char str[1024];
		
		scanf("%s", &number_count);
		if(atoi(number_count) != gen->num_int){
			fprintf(stderr, "The num_int given and num_int inside input file is not the same\n");
			free(gen);
			exit(1);
		}
		nums = (int *)malloc(gen->num_int*sizeof(int));
		if(nums == NULL){
			perror("Memory for array cannot be allocated : ");
			free(gen);
			exit(1);
		}
		int index = 0;
		while(index < (gen->num_int)){
			scanf("%s", &str);
			nums[index] = atoi(str);
			index++;
		}
	}	

	//sort the numbers
	qsort(nums, gen->num_int, sizeof(int), cmpfunc);
	
	//show output for sorted numbers
	if(gen->out_flag){
		FILE *output_fp = fopen(gen->f_out, "w");
		if(output_fp == NULL){
			fprintf(stderr, "invalid output file provided\n");
			free(gen);
			fclose(output_fp);
			exit(1);
		}
		for(int x = 0; x < gen->num_int; x++){
			fprintf(output_fp, "%d\n", nums[x]);
		}
		fclose(output_fp);
	}else{
		for(int x = 0; x < gen->num_int; x++){
			printf("%d\n", nums[x]);
		}
	}
	

	//show output for count file	
	if(gen->count_flag){
		FILE *count_fp = fopen(gen->f_count, "w"); 
		if(count_fp == NULL){
			fprintf(stderr, "invalid count file provided\n");
			free(gen);
			fclose(count_fp);
			exit(1);
		}
		for(int x = 0; host[x] != '\0'; x++){
			fprintf(count_fp, "%c\t%d\t%d\n", host[x], host[x], count_freq(nums, gen->num_int, host[x]));
		}
		fclose(count_fp);
		
	}
	else{
		for(int x = 0; host[x] != '\0'; x++){
			printf("%c\t%d\t%d\n", host[x], host[x], count_freq(nums, gen->num_int, host[x]));
		}
	}

	
	free(nums);
	free(gen);
	get_time(&end);
	diff_time(&start, &end, &result);
	print_time(&result);
	
	return 0;
}
