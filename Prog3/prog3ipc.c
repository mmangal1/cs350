#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
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

void signal_handler(int signal){

}

void child_function(){
	signal(SIGUSR1, signal_handler);
	pause();
}

int main(int argc, char* argv[]){
	char* num_procs_char = argv[1];
	
	//create named pipe
	int fd;
	char *myFifo = "/tmp/myFifo";
	mkfifo(myFifo, 0666);
	
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
	shm_fd = shm_open(name, O_CREAT|O_RDWR, 0666);
	if(shm_fd < 0){
		fprintf(stderr, "shared memory not created");
		exit(1);
	}
	ftruncate(shm_fd, SIZE);
	
	void *start_ptr;
	start_ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	//adding top_level_pid to shared memory
	int top_level_pid = getpid();
	memcpy(start_ptr, &top_level_pid, sizeof(int));
	
	void *ptr = start_ptr;
	//incrementing shared memory pointer
	ptr += sizeof(int);

	int level = num_procs;

	pid_t pid;
	printf("level %d child %d parent %d\n", num_procs, getpid(), getppid());
	for(int i = 0; i < num_procs-1; i++){
		int pfds[2];
		char buf[30];
		if(pipe(pfds) == -1){
			perror("pipe");
			exit(1);
		}	

		pid = fork();
		level--;
		
		if(pid < 0){
			fprintf(stderr,"Forking error\n");
			exit(1);
		}else if(pid == 0){
			printf("level %d child %d parent %d\n", num_procs-i-1, getpid(), getppid());
			int pid = getpid();
		
			//shared memory:	
			memcpy(ptr, &top_level_pid, sizeof(int));
			//incrementing shared memory pointer
			ptr += sizeof(int);

			//pipe:
			close(pfds[1]); //close the write end
			if(read(pfds[0], buf, 30) <= 0){
				perror("child read error\n");
				exit(1);
			}

			if(atoi(buf) == 1){
				fd = open(myFifo, O_WRONLY);
				write(fd, "Leaf final level reached", sizeof("Leaf final level reached"));
				close(fd);
				child_function();	
			}
			unlink(myFifo);				
			
		}else{
			close(pfds[0]); //close the read end
			char level_write[30];
			snprintf(level_write, 30, "%d", level);
			if(write(pfds[1], level_write, 30) <= 0){
				perror("write error parent\n");
				exit(1);
			}	
			
			break;
		}
	}

	if(top_level_pid != getpid()){
		child_function();
	}else{
		
	}
	wait(NULL);	

	return 0;
}
