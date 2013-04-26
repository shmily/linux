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

#define	PACKET_START	"A5 5A 12 A1 "
#define	PACKET_END		" AA A5 5A "


float cover(unsigned char * pstr);
void out_put(FILE * fd, unsigned char *pstr);

int main(int argc, char *argv[])
{
	FILE * 	input_fd;
	FILE * 	output_fd;
	unsigned char   buff[513];
	unsigned char   tmp[513];
	unsigned char   message[64];
	int		index;
	size_t	len;

	unsigned char *pstart;
	unsigned char *pstr;
	unsigned char *pend;
	unsigned char *plast;

	int packet_len;

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

	do{
		memset(buff, 0, sizeof(buff));
		len = fread(buff, 1, 512, input_fd);
		pstr = buff;

		while(1){
			pstart = strstr(pstr, PACKET_START);
			pend   = strstr(pstr, PACKET_END);

			if((pstart!=NULL) && (pend!=NULL)){
				if(pstart < pend){
					packet_len = (pend - pstart - strlen(PACKET_START));

					if(packet_len==44){
						memset(message, 0, sizeof(message));
						memcpy(message,pstart+strlen(PACKET_START), packet_len);
						out_put(output_fd, message);
					}

					pstr = pend;
					plast = pend;
				} else {
					pstr = pstart;
				}
			} else {
				break;
			}
		}

		lseek(input_fd, plast-(buff+512), SEEK_CUR);

	}while(len==512);

	fclose(input_fd);
	fclose(output_fd);

	cover("86 5B");

	return 0;
}


unsigned char ascii2hex(unsigned char i)
{
	unsigned char ret;
	if(i>='A') ret = (i - 'A') + 10;
	else 	   ret = i - '0';

	return ret;
}

//void cover(FILE *fd, unsigned char * pstr)
float cover(unsigned char * pstr)
{
	unsigned char tmp1, tmp2;
	unsigned char num1, num2;;

	int			  res;
	float		  res_f;

	tmp1 = ascii2hex( *(pstr++) );
	tmp2 = ascii2hex( *(pstr++) );

	num1 = 0;
	num1 = tmp1;
	num1 = (num1 << 4) | tmp2;

	pstr++;

	tmp1 = ascii2hex( *(pstr++) );
	tmp2 = ascii2hex( *(pstr++) );

	num2 = 0;
	num2 = tmp1;
	num2 = (num2 << 4) | tmp2;

	res = 0;
	res = num1;
	res = res << 8 | num2;

	if(res&0x8000){
		res = 0-(res&0x7fff);
	}else res = (res&0x7fff);
	
	res_f = (float) res / 10.0f;

	printf("%f\n", res_f);

	return res_f;
}

void out_put(FILE * fd, unsigned char *pstr)
{
	float res;
	int i;

	for(i=0; i<7; i++){
		res = cover(pstr);
		fprintf(fd, "%f ", res);
		pstr = pstr+6;
	}

	fprintf(fd, "\n");
}
