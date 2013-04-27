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
#include <memory.h>
#include <ctype.h>

int is_break(char *p)
{
	if((*p==' ')||(*p==',')||(*p=='.')||(*p=='?')||(*p=='!')||(*p==';')||(*p=='\0')) return 1;
	else return 0;	
}

int main( void )
{
	char str[1028];
	char out[1028];
	
	int  new_word;
	char *pstr, *pout;

	memset(str, 0, 1028);
	memset(out, 0, 1028);
	scanf("%[^\n]", str);
	
	pstr = str;
	pout = out;
	new_word = 1;
	while(*pstr!='\0'){

		if( is_break(pstr) == 1){
			new_word = 1;
			*pout = *pstr;
		}else{
			if(new_word == 1){
				new_word = 0;
				if(((*pstr) == 'w')||((*pstr)=='W')){
					if(  tolower(*(pstr+1))=='e' && is_break(pstr+2)==1 ){
						if(*pstr<'w') *pout++ = 'Y';
						else *pout++ = 'y';

						if(*(pstr+1)<'e'){
							*pout++= 'O';
							*pout= 'U';
						}else{
							*pout++= 'o';
							*pout= 'u';
						}

						pstr = pstr + 1;
					}else{
						*pout = *pstr;
					}
				} else if(((*pstr) == 'Y')||((*pstr)=='y')){
					if( tolower(*(pstr+1))=='o' && tolower(*(pstr+2))=='u' && is_break(pstr+3)==1 ){
						if(*pstr<'y') *pout++ = 'W';
						else *pout++ = 'w';

						if(*(pstr+1)<'o'){
							*pout= 'E';
						}else{
							*pout = 'e';
						}

						pstr = pstr + 2;
					}else{
						*pout = *pstr;
					}
				}else{
					*pout = *pstr;
				}
			} else {
				*pout = *pstr;
			}
		}
		pout++;
		pstr++;
	}

	printf("%s\n",out);
    return 0;
}
