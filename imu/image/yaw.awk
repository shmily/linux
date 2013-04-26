#!/bin/awk -f

{
	printf "%-4s %s %s %s\n", NR*0.4, $1, $2-3.6, $3;
}
