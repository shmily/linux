#include<stdio.h>
#include<math.h>
int main()
{ int m,i,j,k,c;
int a[100];
int n=0;
scanf("%d",&m);
if((m>1)&&(m<100))
for(j=1;j<=m;j++)
{k=sqrt(j);
for(i=2;i<=k;i++)
  if(j%i==0)break;
if(i>k){c=0;}
else{ c=1;}
if(c==1)
a[n++]=j;
}
for(i=0;i<n-1;i++)
	printf("%d ",a[i]);


printf("%d",a[i]);

printf("\n");
return 0;
}
