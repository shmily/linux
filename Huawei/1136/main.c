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

int check_id(char *str);

int main(void)
{
	char str[32];
	int  err;

	gets(str);

	err = check_id(str);
	printf("%d\n", err);


    return err;
}

int check_id(char *str)
{
	int  i, year, mon, day;
	char *p;

	int _mday[13] = {0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if(strlen(str)!=18) return 1;

	p = str;
	for(i=0; i<17; i++){
		if((*p<'0')||(*p>'9')){
			return 2;
		}
		p++;
	}

	if( ((*p>='0')&&(*p<='9')) || (*p=='x') ){
		year = (str[6]-'0')*1000 + 
			   (str[7]-'0')*100 + 
			   (str[8]-'0')*10+
			   (str[9]-'0');

		mon = (str[10]-'0')*10 +
			  (str[11]-'0');

		day = (str[12]-'0')*10 +
			  (str[13]-'0');

	}else{
		return 3;
	}

	if((year<1900)||(year>2100)) return 4;
	if((mon<1)||(mon>12)) return 5;

	if(mon==2){
		if((day<1)||(day>29)) return 6;
		else if(day==29){
			if(((year%4==0)&&(year%100!=0))||(year%400==0)){
				;
			}else{
				return 6;
			}
		}
	}else{
		if((day<1)||(day>_mday[mon])){
			return 6;
		}
	}

	return 0;
}
