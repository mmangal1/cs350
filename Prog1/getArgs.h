#ifndef GETARGS_H
#define GETARGS_H

struct arguments{
	int in_flag;
	int out_flag;
	int count_flag;
	int num_int;
	int min_int;
	int max_int;
	char *f_out;
	char *f_count;
	char *f_in;
	char *host;
	int seed_flag;
	unsigned long seed;
};

struct arguments *get_args(int argc, char **argv);
int check_digit(char* optarg);

#endif
