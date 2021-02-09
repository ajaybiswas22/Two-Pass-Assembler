#include<stdio.h>
#include<string.h>
struct Pstab
{
	char pins[6];
	int pvalue;
}ps;

int main(void)
{
	int i,val,n;
	char instruct[6];
	FILE *fp1;
	fp1=fopen("pstab.dat","w");
	
	printf("Enter Number of Entries : ");
	scanf("%d",&n);
	printf("Enter Data\n");
	
	for(i=0;i<n;i++)
	{
		printf("Enter Instruction : ");
		scanf("%s",&instruct);
		printf("Enter value : ");
		scanf("%d",&val);
		strcpy(ps.pins,instruct);
		ps.pvalue=val;
		fwrite(&ps,sizeof(ps),1,fp1);		
	}
	
	fclose(fp1);
	
	return 0;
}
