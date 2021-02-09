#include<stdio.h>
#include<string.h>
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
	int i,val,n,si;
	char instruct1[6],instruct2[6],instruct3[6];
	FILE *fp3;
	fp3=fopen("mottab.dat","w");
	
	printf("Enter Number of Entries : ");
	scanf("%d",&n);
	printf("Enter Data\n");
	
	for(i=0;i<n;i++)
	{
		printf("Enter Instruction P1: ");
		scanf("%s",&instruct1);
		printf("Enter Instruction P2: ");
		scanf("%s",&instruct2);
		printf("Enter Instruction P3: ");
		scanf("%s",&instruct3);
		printf("Enter value : ");
		scanf("%d",&val);
		printf("Enter Size : ");
		scanf("%d",&si);
		strcpy(mot.ins1,instruct1);
		strcpy(mot.ins2,instruct2);
		strcpy(mot.ins3,instruct3);
		mot.value=val;
		mot.size=si;
		fwrite(&mot,sizeof(mot),1,fp3);		
	}
	
	fclose(fp3);
	
	return 0;
}
