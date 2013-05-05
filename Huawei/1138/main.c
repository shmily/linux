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
#include <ctype.h>

#define _MAX_WORD_LEN	64

struct list_t
{
	char word[_MAX_WORD_LEN];
	int  id;
	struct list_t *next;
};

int gID = 0;
struct list_t list_head;

int  cmd_process(char *pstr);
int  cmd_set(char *world1, char *world2);
int  cmd_search(char *word1, char *word2);
void cmd_clear(void);

void list_add(char *word, int id);
int  list_search(char *word);
void list_update(int old_id, int new_id);
void list_clear(void);

int main(void)
{
	char input[1024];

	while(scanf(" %[^\n]", input)!=EOF){
		cmd_process(input);
	}
	list_clear();
    return 0;
}

//-----------------------------------------

int param_parser(char *pstr, int len, char *param1, char *param2, int num);
int cmd_process(char *pstr)
{
	char *p;
	int  i, len, ret;
	char param1[_MAX_WORD_LEN];
	char param2[_MAX_WORD_LEN];

	len = strlen(pstr);
	p = pstr;
	for(i=0; i<len; i++){
		if(isalnum(*p)==0) *p = 0;
		p++;
	}

	p = pstr;
	while(*p==0) p++;	// skip the space.
	if(strcmp(p, "SetSynonyms")==0){
		ret = param_parser(pstr, len, param1, param2, 3);
		if(ret==0){
			if(cmd_set(param1, param2)!=0){
				printf("false\n");
			}
		}
	}else if(strcmp(p, "IsSynonyms")==0){
		ret = param_parser(pstr, len, param1, param2, 3);	
		if(ret==0){
			if(cmd_search(param1, param2)==0){
				printf("true\n");
			}else{
				printf("false\n");	
			}
		}
	}else if(strcmp(p, "ClearRelations")==0){
		ret = param_parser(pstr, len, param1, param2, 1);
		if(ret==0){
			cmd_clear();
		}
	}else{
		printf("error:系统不支持该命令\n");
		return -1;
	}

	return 0;
}

int param_parser(char *pstr, int len, char *param1, char *param2, int num)
{
	int i, cnt;
	int pos[2];

	pos[0] = 0;
	pos[1] = 0;
	cnt = 0;
	i = 0;
	while(i<len){
		while((pstr[i]==0)&&(i<len)) i++;
		if(i>=len) break;

		cnt++;
		if(cnt>num){	// too much param
			break;
		}else if(cnt==2){
			pos[0] = i;
		}else if(cnt==3){
			pos[1] = i;
		}

		while(pstr[i]!=0) i++;
	}

	if(cnt<num){
		printf("error:参数过少\n");
		return -1;
	}else if(cnt>num){
		printf("error:参数过多\n");
		return -1;
	}else{
		strcpy(param1, pstr+pos[0]);
		strcpy(param2, pstr+pos[1]);
	}

	return 0;
}


//------------------------------------------

int cmd_set(char *world1, char *world2)
{
	int id1, id2;
	int old_id, new_id;

	if(strcmp(world1, world2)==0){
		return -1;
	}

	id1 = list_search(world1);
	id2 = list_search(world2);

	if(id1==id2){
		if(id1==-1){
			gID++;
			list_add(world1, gID);
			list_add(world2, gID);
		}else{
			return -1;
		}
	}else{
		if(id1==-1){
			list_add(world1, id2);
		}else if(id2==-1){	
			list_add(world2, id1);
		}else{
			old_id = id1>id2?id1:id2;
			new_id = id1>id2?id2:id1;
			list_update(old_id, new_id);
		}
	}

	return 0;
}

int cmd_search(char *word1, char *word2)
{
	int id1, id2;

	if(strcmp(word1, word2)==0){
		return -1;
	}

	id1 = list_search(word1);
	id2 = list_search(word2);

	if((id1==id2)&&(id1!=-1)){
		return 0;
	}else{
		return -1;
	}
}

void cmd_clear(void)
{
	gID = 0;
	list_clear();
}

//------------------------------------------

void list_add(char *word, int id)
{
	struct list_t *p;
	
	p = (struct list_t *)malloc(sizeof(struct list_t));

	strcpy(p->word, word);
	p->id = id;

	p->next = list_head.next;
	list_head.next = p;
}

int list_search(char *word)
{
	int id;
	struct list_t *curr;

	id = -1;
	curr = list_head.next;
	while(curr!=NULL){
		if(strcmp(curr->word, word)==0){
			id = curr->id;
			break;
		}
		curr = curr->next;
	}

	return id;
}

void list_update(int old_id, int new_id)
{
	struct list_t *curr;

	curr = list_head.next;
	while(curr!=NULL){
		if(curr->id==old_id){
			curr->id = new_id;
		}
		curr = curr->next;
	}
}

void list_clear(void)
{
	void *p;
	struct list_t *curr;

	curr = list_head.next;
	list_head.next = NULL;
	while(curr!=NULL){
		p = curr;
		curr = curr->next;
		free(p);
	}
}

