/*
=============================================================================
#
#        Author : shmily - shmily@mail.dlut.edu.cn
#            QQ : 723103903
# Last modified : 2013-04-12 20:11
#      Filename : main.c
#   Description : not thing...
#
=============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	FILE * 	input_fd;
	FILE * 	output_fd;
	char   	buff[512];
	char    message[32];
	int		index;
	size_t	len;

	if(argc != 2){
		printf("Error input!\nUsages : Parser path_to_file\n");
		exit(1);
	}

	// open the input file.
	input_fd = fopen(argv[1],"r");
	if(input_fd == NULL){
		perror("open file");
		exit(1);
	}

	// create a new file to save the data.
	output_fd = fopen("./out.txt","w");
	if(input_fd == NULL){
		perror("create file");
		exit(1);
	}

	len = fread(buff, 512, 1, input_fd);

	while(len>0){
		
	}

	fclose(input_fd);
	fclose(output_fd);

	return 0;
}


