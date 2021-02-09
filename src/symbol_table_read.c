#include<stdio.h>

struct Symbtab
{
	char name[10];
	int offset;
	char data[10];
}sy;

int main(void)
{
	FILE *fp1;
	
	if((fp1 = fopen("symboltab.dat","r"))==NULL)
		{
 			 printf("\nError in Opening File");
 			 exit(0);
  		}
  		while((fread(&sy,sizeof(sy),1,fp1)))
		{
 			printf("\nName : %s",sy.name);
 			printf("\nOffset : %d",sy.offset);
 			printf("\nData : %s",sy.data);
		}
		fclose(fp1);
		
	return 0;
}
