
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define _ge_input_ip( _ip) scanf("%d.%d.%d.%d", (_ip), (_ip+1), (_ip+2), (_ip+3))

int ip_valid(int *ip)
{
    int t;

	if((*ip==127)||(*ip>=255)||(*ip==0)) 
		return 0;

    t = (*(ip+1)&0xFFFFFF00) + (*(ip+2)&0xFFFFFF00) + (*(ip+3)&0xFFFFFF00);
    if(t>0)
		return 0;

	return 1;
}

int mask_valid(int *mask)
{
	unsigned int b;
	b = (unsigned int)*mask;

	if((b==0xFFFFFFFF)||(b==0x00)) return 0;

	b = ~b + 1;
	b = b&(b-1);
	return (b==0)?1:0;
}

int main(void)
{
	int ip[4];
	int mask[4];
	int i, count;

	int local, _mask, tmp;


	_ge_input_ip(ip);
	if(ip_valid(ip) == 0){
		printf("Invalid IP adress.\n");
		exit(0);
	}
	local = (ip[0]<<24) + (ip[1]<<16) + (ip[2]<<8) + ip[3]; 

	_ge_input_ip(mask);
	_mask = (mask[0]<<24) + (mask[1]<<16) + (mask[2]<<8) + mask[3]; 
	if(mask_valid(&_mask) == 0){
		printf("Invalid netmask adress.\n");
		exit(0);
	}

	local = local & _mask;

	scanf("%d", &count);

	for(i=0; i<count; i++){
		
		_ge_input_ip(ip);
		if(ip_valid(ip) == 0){
			printf("Invalid IP adress.\n");
			continue;
		}

		tmp = (ip[0]<<24) + (ip[1]<<16) + (ip[2]<<8) + ip[3];
		tmp = tmp & _mask;

		if(tmp == local){
			printf("let's rock\n");
		}else{
			printf("not you\n");	
		}
	}

	exit(0);
}
