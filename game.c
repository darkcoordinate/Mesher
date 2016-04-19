#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct pos{
	float x,y;
}pos;
int main()
{
	pos p[10];
	
	for(int i = 0; i < 10; i++)
	{
		p[i].x = (float)(rand()%4);
		p[i].y = (float)(rand()%100);
	}
	for(int i = 0; i < 10; i++)
	{
		printf("p %d: %f %f\n",i,p[i].x,p[i].y);
	}
	return 0;
}	
