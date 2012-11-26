/*=============================================================================
#
#        Author : shmily - shmily@mail.dlut.edu.cn
#            QQ : 723103903
# Last modified : 2012-11-25 08:36
#      Filename : Timer.c
#   Description : not thing...
#
=============================================================================*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>  
#include <signal.h>

int set_ticker(int n_msecs)
{
	struct 	itimerval timer;
	long	n_sec, n_usec;

	n_sec  = n_msecs / 1000;
	n_usec = (n_msecs % 1000)*1000L; 

	timer.it_interval.tv_sec = n_sec; 		/* set reload */  
	timer.it_interval.tv_usec = n_usec;  

	timer.it_value.tv_sec = n_sec;    		/* set new ticker value */  
	timer.it_value.tv_usec = n_usec; 

	return setitimer(ITIMER_REAL, &timer, NULL);  
}
