#include <stdio.h>
 
void hanoi( int n, char start, char middle, char end );

int main()
{
    int n = 0;
    
    printf( "input the number of plates;\n" );
    scanf( "%d", &n );
    hanoi( n, 'A', 'B', 'C' );
    
    return 0;
}

void hanoi( int n, char start, char middle, char end )
{
    if( n == 1 )
    {
        printf( "will move %d from %c to %c.\n", n, start, end );
    }
    else
    {
        hanoi( n - 1, start, end, middle );
        printf( "will move %d from %c to %c.\n", n, start, end );
        hanoi( n - 1, middle, start, end );
    }
}
