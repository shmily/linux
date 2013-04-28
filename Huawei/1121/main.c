
#include <stdio.h>
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
	int i;
	int div;
	int *p;

	div = -1;
	p = mask;
	for(i=0; i<4; i++){
		if(div == -1){
			if( ((*p)&0xFF) != 0xFF ){
				div = i;
			}
		}else{
			if( ((*p)|0x00) != 0x00 ){
				return 0;
			}
		}
		p++;
	}

	if(div == -1) return 0;
	if( div == 0 && (*mask)==0x00 ) return 0;

	div = *(mask+div);

    switch(div){
        case 0x80:
        case 0xC0:
        case 0xE0:
        case 0xF0:
        case 0xF8:
        case 0xFC:
        case 0xFE:
        case 0x00:
            i = 1;
            break;
        default:
            i = 0;
            break;
    }

	return i;
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
		goto _exit;
	}

	_ge_input_ip(mask);
	if(mask_valid(mask) == 0){
		printf("Invalid netmask adress.\n");
		goto _exit;
	}

	local = (ip[0]<<24) + (ip[1]<<16) + (ip[2]<<8) + ip[3]; 
	_mask = (mask[0]<<24) + (mask[1]<<16) + (mask[2]<<8) + mask[3]; 
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

_exit:
    return 0;
}
