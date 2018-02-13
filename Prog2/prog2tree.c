#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
void sig_handlr(int signo){
	printf("EXITING: Level %d process with pid=%d, child of ppid=%d\n", 1, getpid(), getppid());
}

int main(int argc, char *argv[]){
	
	int option;
	int num_levels, num_children, sleep_time, sleep_flag, pause_flag;
	num_levels = 1;
	sleep_flag = pause_flag = 0;
	num_children = 1;
	sleep_time = 1;
	char* params[100];
	int argv_index = 1;
	int num_level_index = 1;
	while((option = getopt(argc, argv, ":uN:M:ps:")) != -1){
		switch(option){
			case 'u':
				fprintf(stderr, "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]\n");
				exit(1);
			case 'N':
				if(check_digit(optarg)){
					num_levels = atoi(optarg);
					if(num_levels > 4){
						fprintf(stderr,"num_levels needs to be less than 4\n");	
						exit(1);
						}		
				}else{
					fprintf(stderr,"num_levels needs to be an integer less than 4\n");	
					exit(1);
				}
				num_level_index = argv_index;
				break;
			case 'M':
				if(check_digit(optarg)){
					num_children = atoi(optarg);
					if(num_children > 3){
						fprintf(stderr,"num_children needs to be less than 3\n");	
						exit(1);		
					}
				}else{
					fprintf(stderr,"num_children needs to be an integer less than 3\n");	
					exit(1);
				}
				argv_index += 2;
				break;
			case 'p':
				pause_flag = 1;
				argv_index++;	
				break;
			case 's':
				if(check_digit(optarg)){
					sleep_flag = 1;
					sleep_time = atoi(optarg);
				}else{
					fprintf(stderr,"sleep_time needs to be an integer\n");	
					exit(1);
				}
				argv_index += 2;
				break;
			case '?':
				fprintf(stderr, "invalid option provided\n");
				exit(1);
			default:
				break;
		}
	}
	
	if(!sleep_flag && !pause_flag){
		sleep_time = 1;
	}else if(sleep_flag && pause_flag){
		fprintf(stderr, "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]\n");
		exit(1);
	}

	printf("ALIVE: Level %d process with pid=%d, child of ppid=%d\n", num_levels, getpid(), getppid());
	
	pid_t pid;
	if(num_levels > 1){
		for(int x = 0; x < num_children; x++){
			if((pid = fork()) < 0){
				perror("fork");
				exit(1);
			}
			if(pid == 0){
				sprintf(argv[num_level_index +1],"%d", num_levels-1);
				execvp(argv[0], argv);
			}
		}
		for(int i = 0; i < num_children; i++){
			wait(NULL);
		}
	}

	if(num_levels == 1){
		signal(SIGINT, sig_handlr);	
		if(sleep_flag)
			sleep(sleep_time);
		else if(pause_flag)
			pause();
	}
	printf("EXITING: Level %d process with pid=%d, child of ppid=%d\n", num_levels, getpid(), getppid());
	return 0;
}
