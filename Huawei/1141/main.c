/*
=============================================================================
#
#        Author : shmily - shmily@mail.dlut.edu.cn
#            QQ : 723103903
# Last modified : 2013-04-18 20:47
#      Filename : Pascal.c
#   Description : not thing...
#
=============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define _MAX_PACKET		20

struct packet_t
{
	int tag;
	int tag_index;
	int len;
};

struct packet_t packet[_MAX_PACKET];
struct packet_t *pointer[_MAX_PACKET];

void packet_dump(int cnt);
void _packet_dump(int cnt);
void packet_sort(int cnt);

int main(int argc, char *argv[])
{	
	int data[100];
	int i, data_len, packetCnt;
	int *pdata;
	struct packet_t *p;

	// input
	pdata = data;
	while(scanf("%x", pdata++)==1){
		if(','!=getchar())
			break;
		getchar();
	}
	data_len = (pdata - data);

	// parse the packets
	p = packet;
	for(i=0; i<data_len; ){
		p->tag = (data[i]<<24)|(data[i+1]<<16)|
				(data[i+2]<<8)|(data[i+3]);

		p->tag_index = i;
		p->len = ((data[i+4]<<8)|(data[i+5]))+4+2;
		i += p->len;
		p++;
	}
	if(i!=data_len){
		printf("false\n");
		return 0;
	}
	packetCnt = p - packet;

	printf("packet cnt : %d\n", packetCnt);

	packet_dump(packetCnt);


	packet_sort(packetCnt);

    return 0;
}

void packet_sort(int cnt)
{
	int i,j;
	struct packet_t *tmp;

	for(i=0; i<cnt; i++){ pointer[i] = &packet[i]; }

	for(i=0; i<cnt; i++){
		for(j=1; j<cnt-i; j++){
			if(pointer[j-1]->tag > pointer[j]->tag){
				tmp = pointer[j-1];
				pointer[j-1] = pointer[j];
				pointer[j] = tmp;
			}
		}
	}

	_packet_dump(cnt);
}

void packet_dump(int cnt)
{
	int i;

	for(i=0; i<cnt; i++){
		printf("---------------\n");
		printf("tag        : 0x%08x\n", packet[i].tag);
		printf("tag index  : %d\n",     packet[i].tag_index);
		printf("packet len : %d\n",     packet[i].len);
	}
}

void _packet_dump(int cnt)
{
	int i;

	for(i=0; i<cnt; i++){
		printf("++++++++++++++++++++++\n");
		printf("tag        : 0x%08x\n", pointer[i]->tag);
		printf("tag index  : %d\n",     pointer[i]->tag_index);
		printf("packet len : %d\n",     pointer[i]->len);
	}
}
