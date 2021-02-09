#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	FILE *fp1;
	char ch[50];
	if((fp1 = fopen("objcode.txt","r"))==NULL)
		{
 			 printf("\nError in Opening File");
 			 exit(0);
  		}
  	while( fgets (ch,50, fp1 ) != NULL )
{
	printf("%s",ch);
}
		fclose(fp1);
		
	return 0;
}
