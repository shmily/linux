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

// old, middle, young, junior, children
const double _rate[8][5] = 
{
	{ 70.00,  90.00, 300.00, 600.00, 1000.00}, // male, single,  no smoking
	{ 70.00,  95.00, 450.00, 750.00, 1000.00}, // male, single,     smoking
	{200.00, 300.00, 600.00, 900.00, 1000.00}, // male, married, no smoking
	{250.00, 350.00, 650.00, 900.00, 1000.00}, // male, married,    smoking

	{100.00, 105.00, 400.00, 600.00, 1000.00}, // female, single,  no smoking
	{105.00, 120.00, 450.00, 700.00, 1000.00}, // female, single,     smoking
	{250.00, 400.00, 650.00, 850.00, 1000.00}, // female, married, no smoking
	{250.00, 500.00, 700.00, 900.00, 1000.00}  // female, married,    smoking
};

int main(void)
{
	int male, single, smok, age;
	int i;

	scanf("%d,%d,%d,%d", &male, &single, &age, &smok);

	i = (male<<2) | (single<<1) | smok;
	printf("%0.2f\n", _rate[i][age]);

    return 0;
}
