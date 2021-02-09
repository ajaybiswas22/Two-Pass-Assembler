#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void motread();
void symbolread();
void psread();
void pass1();
void pass2();
void parfun(char *,char *,int);
void parfun2(int,char *);
int tempinc=0;
char beglo[10];
struct Symbtab            //Symbol Table
{
	char name[10];
	int offset;
	char data[10];
	
}sy;

struct Mactab
{
	char ins1[6];
	char ins2[6];
	char ins3[6];
	int value;
	int size;
}mot;

struct Objtab            //Object code table (pass2)
{
	char addr[8];
	int motdata;
	int symoff;
}ob;

struct Pstab             //Pseudo Opcode Table
{
	char pins[6];
	int pvalue;
}ps;

int offs=0;              // Beg offset
	FILE *fp1,*fp2,*fp3,*fp4;
	
int main(void)
{

	pass1();
	pass2();
	symbolread();
	motread();
	psread();
	return 0;
}

void pass1()
{
	FILE *fp1,*fp2,*fp3,*fp4;
	int j,i,k,flag=0,psflag=0;
	int next1,next2,gh;
	char ch[50],initial[10],x[50],mid[10],last[10];
	printf("\nPASS 1\n");
	if((fp1=fopen("instruction.txt","r"))==NULL)                   // Instruction text file
	{ 
  printf("\nError in Opening File");
  exit(10);
  }

	if((fp2 = fopen("symboltab.dat","wb+"))==NULL)      // symboltable
  { 
  printf("\nError in Opening File");
  exit(11);
  }
	
while( fgets (ch,50, fp1 ) != NULL )                     // Reading instructions
{
	printf("%s",ch);
	if(strncmp(ch,"END",3)==0)                           // Checking For END
	{
		break;
	}
	else if(strcmp(ch,"\n")==0)
	{
		continue;
	}
	strcpy(x,ch);
                                                         // String Parsing
	for(i=0;x[i]!=' ';i++)
	{
		initial[i]=x[i];
	    next1=i;
	} 
	initial[i]='\0';
//	printf("%s.",initial);                               First part

	if(strcmp(initial,"START")==0)                        // Start
	{
		continue;
	}
		for(i=next1+2,k=0;x[i]!=' ';i++,k++)
					{
					mid[k]=x[i];
					next2=i;
	 				}
                    mid[k]='\0';
	     //   printf("%s\n",mid);                           Middle
	        
			sy.offset=offs;                                  //Assigning offset
		if((fp4 = fopen("pstab.dat","r"))==NULL)             // Pseudo Opcode Table Search
		{
 			 printf("\nError in Opening File");
 			 exit(12);
  		}				
					while((fread(&ps,sizeof(ps),1,fp4)))
		{		
			if(strcmp(mid,ps.pins)==0)
	    	{
	    		
				offs=offs+ps.pvalue;
				psflag=1;
			}
			
		}
					if(psflag==0)
					offs=offs+0;
		
	             
				 for(i=next2+2,k=0;x[i]!=' ';i++,k++)
					{
					last[k]=x[i];
	 				}
	  				last[k]='\0';

	          /*    gh=strlen(last)-1;
	  				  last[gh]='\0';
	  				  */
	      //  printf("%s",last);                                  
	  	   
			   			
			if((fp3 = fopen("mottab.dat","r"))==NULL)                //Machine Opcode Table Search
		{
 			 printf("\nError in Opening File");
 			 exit(13);
  		}			
  		while((fread(&mot,sizeof(mot),1,fp3)))
		{
 			if(strcmp(mot.ins1,initial)==0)
			{
				flag=1;
			}
		}
			if(flag==0)
			{
				
				printf("Writing in symbol table %s\n",initial);
			
				strcpy(sy.name,initial);
				strcpy(sy.data,last);
				
			 fwrite(&sy,sizeof(sy),1,fp2);	
	
			}
	
	// Resetting all Values
			
		for(i=0;i<10;i++)                                            
		{
			initial[i]='\0';
			mid[i]='\0';
			last[i]='\0';
			
		}
		
		flag=0;
		psflag=0;
		fclose(fp3);
		fclose(fp4);
	
}                                            // End of Instruction file read loop
  	
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	printf("\nPass 1 finished\n\n");
	
} 

void pass2()
{
	int j,i,gh,k,inc=0;
	int next1,next2,flag2=0,exflag=0;
	char ch[50],initial[10],x[50],mid[10],last[10],temp[10],mid2[10],midtemp[10];
	
	printf("PASS 2\n");
	if((fp1=fopen("instruction.txt","r"))==NULL)
	{
		 printf("nError in Opening File");
  			exit(14);	
	}
    if((fp3 = fopen("objcode.txt","wb+"))==NULL)
  {
  printf("nError in Opening File");
  exit(15);
  }
  printf("Generating Object Code\n");
while( fgets (ch,50, fp1 ) != NULL )
{
	//printf("%s",ch);
	if(strncmp(ch,"END",3)==0)
	{
		break;
	}
		else if(strcmp(ch,"\n")==0)
	{
		continue;
	}
	strcpy(x,ch);
	
	for(i=0;x[i]!=' ';i++)
	{
		initial[i]=x[i];
	    next1=i;
	} 
	initial[i]='\0';
		if(strcmp(initial,"START")==0)
	{
		for(i=next1+2,k=0;x[i]!=' ';i++,k++)
					{
					mid2[k]=x[i];
					next2=i;
	 				}
    			 mid2[k]='\0';
   			  strcpy(beglo,mid2);
   			       inc=atoi(beglo);
	
	}
	else
	{
	
		for(i=next1+2,k=0;x[i]!=' ';i++,k++)
					{
					mid[k]=x[i];
					next2=i;
	 				}
     mid[k]='\0';
	      //     printf("%s\n",mid);
	        strcpy(midtemp,mid);
	                for(i=next2+2,k=0;x[i]!=' ';i++,k++)
					{
					last[k]=x[i];
	 				}
	  last[k]='\0';
	         //    printf("%d",strlen(last));
				
        
	                if((fp4 = fopen("mottab.dat","r"))==NULL)
		{
 			 printf("\nError in Opening File");
 			 exit(0);
  		}	
	
	while((fread(&mot,sizeof(mot),1,fp4)))
		{
			//	printf("%s",midtemp);
				if(strcmp(mot.ins1,initial)==0&&strcmp(mot.ins2,midtemp)==0)
			{
				parfun(last,midtemp,inc);
				exflag=0;
				break;									//	printf("%s",mot.ins);
			}
		
			else if(strcmp(mot.ins1,initial)==0&&strcmp(mot.ins2,midtemp)!=0)
			{
				parfun(last,midtemp,inc);
				exflag=0;
				break;
			}
			else if(strcmp(mot.ins1,initial)==0&&strcmp(mot.ins2,mid)==0)
			{
				parfun(last,midtemp,inc);
				exflag=0;
				break;	
			}
			else
			{
				exflag=1;
			}
	}			
		 if(strcmp(mot.ins1,initial)!=0&&exflag==1)
		{
		
			 if((fp2 = fopen("symboltab.dat","r"))==NULL)
		{
 			 printf("\nError in Opening File");
 			 exit(0);
  		}	
			while((fread(&sy,sizeof(sy),1,fp2)))
		{
						
		    if(strcmp(sy.name,initial)==0)
			{
			//	printf("%s",sy.name);
					parfun2(inc,midtemp);	
					fclose(fp2);	
			}
		}
		
		}
			
			inc=inc+tempinc;
		    inc++;
				  
       	for(i=0;i<10;i++)
		{
			initial[i]='\0';
			mid[i]='\0';
				mid2[i]='\0';
			last[i]='\0';
			
		}	
		flag2=0;
		exflag=0;
		tempinc=0;
		fclose(fp4);
		fclose(fp2);

}
}
	fclose(fp3);
	fclose(fp1);
	fclose(fp2);	
	fclose(fp4);
	printf("Pass 2 Finished");
}

void parfun(char *last,char *mid,int inc)
{
	char temp[10];
	int gh,x;
	int flag2=0;
	 ob.motdata=mot.value;
	 if((fp2 = fopen("symboltab.dat","r"))==NULL)
	 {
  		printf("nError in Opening File");
 		 exit(0);
 	 }	       
	  strcpy(temp,last); 
	  gh=strlen(temp)-1;
	    temp[gh]='\0';

	while((fread(&sy,sizeof(sy),1,fp2)))
		{
	      
	        if(strcmp(temp,sy.name)==0)
	        {
	        	ob.symoff=sy.offset;
	        	 flag2=1;
	   
	       fprintf(fp3,"%d %d %d\n",inc,ob.motdata,ob.symoff);
	      // printf("ffff");
		   printf("%d %d %d\n",inc,ob.motdata,ob.symoff);
		  tempinc=mot.size-1;
	        }
	   }
	   if(flag2==0)
			{
				
				if(*last<1000)
		       {
			     
	 			 fprintf(fp3,"%d %d %d\n",inc,ob.motdata,last);
	 			 printf("%d %d %d\n",inc,ob.motdata,last);
	 			 tempinc=mot.size-1;
	 			 
	 		   }
	 		   else
	 		   {
	 		   		x=atoi(mid);
	 		   		fprintf(fp3,"%d %d %d\n",inc,ob.motdata,x);
	 			 printf("%d %d %d\n",inc,ob.motdata,x);
				tempinc=mot.size-1;
	 			}
			}       
		flag2=0;
}

void parfun2(int inc,char * mid)
{
	
		ob.motdata=0;       
	    ob.symoff=atoi(sy.data);
	   // printf("%s   ",mid);
	    
	    	if((fp4 = fopen("pstab.dat","r"))==NULL)             // Pseudo Opcode Table Search
		{
 			 printf("\nError in Opening File");
 			 exit(0);
  		}				
					while((fread(&ps,sizeof(ps),1,fp4)))
		{		
			if(strcmp(mid,ps.pins)==0)
	    	{
			    	
		  		 tempinc=ps.pvalue-1;
		  	//	 printf("%d",tempinc);
			}
			
		}
				fprintf(fp3,"%d %d %d\n",inc,ob.motdata,ob.symoff);
		  		 printf("%d %d %d\n",inc,ob.motdata,ob.symoff);
	       
		fclose(fp4);   
				
	 	  
}
void symbolread()
{	
	printf("\n\nSYMBOL TABLE \n");
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
		
}

void motread()
{
	printf("\nMACHINE OPCODE TABLE \n");
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
		printf("\n");
		fclose(fp3);
		
}

void psread()
{
		printf("\nPSEUDO OPCODE TABLE\n");
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
		
}



