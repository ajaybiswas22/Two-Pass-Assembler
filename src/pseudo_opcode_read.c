#include<stdio.h>
#include<conio.h>

struct Pstab
{
	char pins[6];
	int pvalue;
}ps;

int main(void)
{
	FILE *fp1;
	
	if((fp1 = fopen("pstab.dat","r"))==NULL)
		{
 			 printf("\nError in Opening File");
 			 exit(0);
  		}
  		while((fread(&ps,sizeof(ps),1,fp1)))
		{
 			printf("\nInstruction : %s",ps.pins);
 			printf("\nValue : %d",ps.pvalue);
		}
		fclose(fp1);
		
	return 0;
}
