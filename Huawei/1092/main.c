
#include <stdio.h>
#include <math.h>

int isPrime(int n)
{
	int i;
	int upper;

	if(n == 2|| n == 3)
		return 1;
	
	if(n % 2 ==0)
		return 0;

	upper = sqrt(n) + 1;
	for(i = 3;i < upper; i += 2){
		if(n %i == 0)
		return 0;
	}

	return 1;
}

int main(void)
{
    int num;

    scanf("%d", &num);
    printf("%d\n", isPrime(num));

    return 0;
}
