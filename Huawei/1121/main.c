
#include <stdio.h>
#include <memory.h>

#define _ge_input_ip(_str, _ip) do{ \
		memset(_str, 0, sizeof(_str)); \
        scanf("%s", _str); \
		sscanf(_str, "%d.%d.%d.%d", (_ip), (_ip+1), (_ip+2), (_ip+3)); \
        }while(0)

#define _get_mask

int ip_valid(int *ip)
{
	if((*ip==127)||(*ip==255)||(*ip==0)) 
		return 0;

	if( *(ip)>255 || *(ip+1)>255 || *(ip+2)>255 || *(ip+3)>255 ) 
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

	if(div == -1) return 0;	// all mask is 255.
	if( div == 0 && (*mask)==0x00 ) return 0; // all mask is 0.

	div = *(mask+div);

	if ( (div==0x80) || (div==0xC0) || (div==0xE0) || (div==0xF0) ||
		 (div==0xF8) || (div==0xFC) || (div==0xFE) || (div==0x00) ){
		return 1;
	}

	return 0;
}

int main(void)
{
    char str[32];
	int ip[4];
	int mask[4];
	int i, count;

	int local, _mask, tmp;

	_ge_input_ip(str, ip);
	if(ip_valid(ip) == 0){
		printf("Invalid IP adress.");
		goto _exit;
	}

	_ge_input_ip(str, mask);
	if(mask_valid(mask) == 0){
		printf("Invalid netmask adress.");
		goto _exit;
	}

	local = (ip[0]<<24) + (ip[1]<<16) + (ip[2]<<8) + ip[3]; 
	_mask = (mask[0]<<24) + (mask[1]<<16) + (mask[2]<<8) + mask[3]; 
	local = local & _mask;

	scanf("%d", &count);

	for(i=0; i<count; i++){
		
		_ge_input_ip(str, ip);
		if(ip_valid(ip) == 0){
			printf("Invalid IP adress.");
			if(i!=count-1) printf("\n");
			continue;
		}

		tmp = (ip[0]<<24) + (ip[1]<<16) + (ip[2]<<8) + ip[3];
		tmp = tmp & _mask;

		if(tmp == local){
			printf("let's rock");
			if(i!=count-1) printf("\n");
		}else{
			printf("not you");	
			if(i!=count-1) printf("\n");
		}
	}

_exit:
    return 0;
}
