
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_LEN 512

struct student_t{
    char             num[8];
    char             name[20];
    char             phone[20];
    struct student_t *next;
};

char *receive;
struct student_t List, *pTail;

int cmd_parser(char *cmd, struct student_t *pin)
{
    int  cmd_type;
    char *p, *pend;

    memset(pin, 0, sizeof(struct student_t));
    memset(receive, 0, MAX_LEN);
    gets(receive);

    cmd_type = -1;
    switch(*receive){
        case 'I':
            p = strstr(receive, "INSERT");
            if(p!=NULL){
                p = p + strlen("INSERT")+1;
                pend = strstr(p, ",");
                if(pend!=NULL){
                    memcpy(pin->num, p, pend - p);
                }else{
                    break;
                }

                p = pend + 1;
                pend = strstr(p, ",");
                if(pend!=NULL){
                    if((pend-p)>16){
                        printf("INSERT INVALID NAME LEN!\n");
                        break;
                    }
                    memcpy(pin->name, p, pend-p);
                }else{
                    break;
                }

                p = pend + 1;
                if(strlen(p)>16){
                    printf("INSERT INVALID TELNO LEN!\n");
                    break;
                }
                strcpy(pin->phone, p);

                cmd_type = 1;
            }
            break;
        case 'S':
            p = strstr(receive, "SELECT");
            if(p!=NULL){
                if(strlen(receive)>strlen("SELECT")){
                    p = p + strlen("SELECT") + 1;
                    strcpy(pin->num, p);
                }
                cmd_type = 2;
            }
            break;
        case 'D':
            p = strstr(receive, "DELETE");
            if(p!=NULL){
                p = p + strlen("DELETE");
                if(*p!='\0'){
                    strcpy(pin->num, p+1);
                    cmd_type = 3;
                }
                else{
                    printf("DELETE NO ID INPUT!\n");
                }
            }
            break;
        case 'Q':
            p = strstr(receive, "QUIT");
            if(p!=NULL){
                cmd_type = 4;
            }
            break;
        default:
            break;
    }

    return cmd_type;
}

struct student_t *list_search(char *num)
{
    struct student_t *p;
    p = &List;

    while(p->next!=NULL){
        if(strcmp(p->next->num, num)==0){
           return p; 
        }else{
            p = p->next;
        }
    }

    return NULL;
}

void list_add(struct student_t *new)
{
    new->next = NULL;
    if(List.next==NULL){
        List.next= new;
        pTail = new;
    }else{
        pTail->next = new;
        pTail = new;
    }
}

void list_del(struct student_t *node)
{
    struct student_t *tmp;

    tmp = node->next->next;
    node->next = tmp;
}

void insert(struct student_t *p)
{
    struct student_t *new;

    if(list_search(p->num)==NULL){
        new = (struct student_t *)malloc(sizeof(struct student_t));
        memset(new, 0, sizeof(struct student_t));

        strcpy(new->num, p->num);
        strcpy(new->name, p->name);
        strcpy(new->phone, p->phone);

        list_add(new);

        printf("INSERT %s,%s,%s SUCCESS.\n", new->num, new->name, new->phone);
    }else{
        printf("INSERT %s,%s,%s ALREADY EXIST.\n", p->num, p->name, p->phone); 
    }
}

void delete(struct student_t *p)
{
    struct student_t *node;

    node = list_search(p->num);

    if(node!=NULL){
        p = node->next;
        printf("DELETE %s,%s,%s SUCCESS.\n", p->num, p->name, p->phone); 
        list_del(node);
        free(p);
    }else{
        printf("DELETE %s FAILED BECAUSE NOT EXIST.\n", p->num); 
    }
}

void print_list()
{
    struct student_t *p;

    p = List.next;
    if(p==NULL) printf("SELECT NULL.\n");
    else
        while(p!=NULL){
            printf("%s,%s,%s\n", p->num, p->name, p->phone);
            p = p->next;
        }
}

void select(struct student_t *p)
{
    struct student_t *node;
    if(strlen(p->num)==0){
        print_list();
    }else{
        node = list_search(p->num);
        if(node==NULL){
            printf("SELECT %s FAILED BECAUSE NOT EXIST.\n", p->num);
        }else{
            node = node->next;
            printf("%s,%s,%s\n", node->num, node->name, node->phone);
        }
    }
}

void quit(void)
{
    struct student_t *p;
    free(receive);

    while(List.next!=NULL){
        p = List.next;
        List.next = List.next->next;
        free(p);
    }
}

int main(void)
{
    struct student_t temp;

    int cmd_type;

    List.next= NULL;
    pTail = NULL;
    receive = malloc(MAX_LEN);

    while(1){
        cmd_type = cmd_parser(NULL,&temp);

        if(cmd_type==1){
            insert(&temp);
        }else if(cmd_type == 3){
            delete(&temp);
        }else if(cmd_type == 2){
            select(&temp);
        }else if(cmd_type == 4){
            break;
        }
    }

    quit();

    return 0;
}
