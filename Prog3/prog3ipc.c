#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
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

int main(int argc, char* argv[]){
	char* num_procs_char = argv[1];
	if(!check_digit(num_procs_char)){
		fprintf(stderr, "./prog3ipc <num-procs>\n");
		exit(1);
	}
	int num_procs = atoi(num_procs_char);

	if(num_procs < 1 || num_procs > 32){
		fprintf(stderr, "num-procs needs to be between 1 and 32 inclusive\n");
		exit(1);
	}

	const char* name = "mmangal1";
	const int SIZE = num_procs * sizeof(int);
	int shm_fd;
	shm_fd = shm_open(name, O_CREAT|O_RDRW, 0666);
	if(shm_fd < 0){
		fprintf(stderr, "shared memory not created");
		exit(1);
	}
	ftruncate(shm_fd, SIZE);
	
	void *ptr;
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	int top_level_pid = getpid();
	memcpy(ptr, &top_level_pid, sizeof(int));
	ptr += sizeof(int);

	int pid;
	printf("level %d child %d parent %d\n", num_procs, getpid(), getppid());
	for(int i = 0; i < num_procs-1; i++){
		pid = fork();
		if(pid < 0){
			fprintf(stderr,"Forking error\n");
			exit(1);
		}else if(pid == 0){
			printf("level %d child %d parent %d\n", num_procs-i-1, getpid(), getppid());
//			printf("ALIVE\n");
		}else{
			break;
		}
	}
	wait(NULL);	

	return 0;
}
