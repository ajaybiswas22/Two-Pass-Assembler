#include<stdio.h>
#include<stdlib.h>

struct Mactab
{
	char ins1[6];
	char ins2[6];
	char ins3[6];
	int value;
	int size;
}mot;

int main(void)
{
	FILE *fp3;
	
	if((fp3 = fopen("mottab.dat","r"))==NULL)
		{
 			 printf("\nError in Opening File");
 			 exit(0);
  		}
  		while((fread(&mot,sizeof(mot),1,fp3)))
		{
 			printf("\nInstruction : %s %s %s",mot.ins1,mot.ins2,mot.ins3);
 			printf("\nValue : %d",mot.value);
 			printf("\nSize : %d",mot.size);
		}
		fclose(fp3);
		
	return 0;
}
