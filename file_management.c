#include <stdio.h>
#include<conio.h>

void insert_record();
void display_record();
void search_record();
void del_record();
void update_record();
void sort_record();

struct student
{
	int roll;
	char sec[10];
	char name[100];
	int marks;
	float grade;
}; struct student s;

void main()
{
	int ch;
	clrscr();
	
	while(ch!=7)
	{
		clrsrc();
		printf("\t\t\t\t\tWELCOME TO STUDENT DATABASE\n\n\n");
		printf("\t\tAvailablr functionalities ::\n\n");
		printf("\t\t1.Insert Student Record.\n");
		printf("\t\t2.Display Student Record.\n");
		printf("\t\t3.Search Student Record.\n");
		printf("\t\t4.Delete Student Record.\n");
		printf("\t\t5.Update Student Record.\n");
		printf("\t\t6.Sort Student Record.\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: clrscr();
			        insert_record();
			        break;
			case 2: clrscr();
			        display_record();
			        break; 
			case 3: clrscr();
			        search_record();
			        break;
			case 4: clrscr();
			        del_record();
			        break;
			case 5: clrscr();
			        update_record();
			        break;		
			case 6: clrscr();
			        sort_record();
			        break;
			case 7: exit(1);
			default :prinft("Wrong choice entered...");								      
		}
		printf("press any key...");
		getch();
	}
}

void insert_record()
{
	FILE *fp;
	fp=fopen("stu.txt","ab+");
	
	if(fp == NULL)
	{
		printf("\nFile cannot find!\n\n");
		return;
	}
	printf("Privious stored data ::\n\n");
	display_record();
	
	printf("\t\t\t\t\tENTER NEW STUDENT DATA\n\n\n");
	fflush(stdin);
	printf("\t\tEnter Roll number:");
	scanf("%d",&s.roll);
	printf("\t\tEnter Student Name:");
	gets(s.name);
	printf("\t\tEnter Student Section:");
	gets(s.sec);
	printf("\t\tEnter Student Total Marks:");
	scanf("%d",&s.marks);
	printf("\t\tEnter Student Grade:");
	scanf("%d",&s.grade);
	fwrite(&s,sizeof(s),fp);
	printf("\t\t\t\t\tSTUDENT DATA INSERT SUCCESSFULLY");
	fclose(fp);
	printf("\t\t\t\t\tUPDATED DATA\n\n");
	display_record();
}
 
void display_record()
{
	FILE *fp;
	fp=fopen("stu.txt","rb");
	
	if(fp==NULL)
	{
		printf("\nFile doesnot exists\n");
		return;
		
	}
	printf("\t\t\t\t\tSTUDENT DETAILS ARE AS FOLLOWS\n\n");
	printf("\nRoll number \tStudent Name \tSection \tTotal Marks \tGrade \n\n");
	
	while(fread(&s,sizeof(s),1,fp)==1)
	{
		printf("%d \t%s  \t%s \t%d \t%.2f\n",s.roll,s.name,s.sec,s.marks,s.grade);
	}
	fclose(fp);
}

void search_record()
{
	int ro,flag=0;
	FILE *fp;
	fp=fopen("stu.txt","rb");
	if(fp==NULL)
	{
		printf("\nFile doesnot exists\n");
		return;	
	}
	printf("Enter student Roll Number which you want to search:");
	scanf("%d",&ro);
	while(fread(&s,sizeof(s),1,fp)>0 && flag==0)
	{
		if(s.roll==ro)
		{
			flag=1;
			printf("\t\tSEARCH SUCCESSFULLY AND SEARCH RESULT IS AS FOLLOWS\n\n");
			printf("\nRoll number \tStudent Name \tSection \tTotal Marks \tGrade \n\n");
			printf("%d \t%s  \t%s \t%d \t%.2f\n",s.roll,s.name,s.sec,s.marks,s.grade);
		}
	}
	
	if(flag==0)
	{
		printf("\t\t\tSEARCH RECORD CAN NOT FOUND\n\n");
	}
	fclose(fp);
}

void del_record()
{
	char name[100];
	unsigned flag=0;
	FILE *fp,*ft;
	fp=fopen("stu.txt","rb");
	if(fp==NULL)
	{
		printf("\nFile doesnot exists\n");
		return;	
	}
	
	printf("\t\t\t\t\tPRIVIOUS STROED DATA\n\n");
	display_record();
	
	printf("\t\tEnter Student Name Which You Want To Delete::");
	sacnf("%s",name);  //
	ft=fopen("stu1.txt","ab+");
	
	while(fread(&s,sizeof(s),1,fp)==1)
	{
		if(strcmp(name,s.name)!=0)
		{
			printf("\t\tRECORD DELETED SUCCESSFULLY\n\n");
			fwrite(&s,sizeof(s),1,ft);
		}
		else{
			flag=1;
		}
	}
	
	fclose(fp);
	fclose(ft);
	remove("stu.txt");
	rename("stu1.txt","stu.txt");
	printf("\n\n\t\t\t\t\tUPDATED RECORD\n\n");
	display_record();
}

void update_record()
{
	int ro,flag=0;
	FILE *fp;
	fp=fopen("stu.txt","rb+");
	if(fp==NULL)
	{
		printf("\nFile doesnot exists\n");
		return;	
	}
	
	printf("\n\n\t\tEnter Roll Number Of The Student Which You Want To Delete::");
	scanf("%d",&ro);
	printf("\n\n\t\t\t\t\tPRIVIOUSLY STROED RECORD OF THE GIVEN ROLL NUMBER\n\n");
	while(fread(&s,sizeof(s),1,fp)>0 && flag==0)
	{
		if(s.roll==ro)
		{
			flag=1;
			printf("\nRoll number \tStudent Name \tSection \tTotal Marks \tGrade \n\n");
			printf("%d \t%s  \t%s \t%d \t%.2f\n",s.roll,s.name,s.sec,s.marks,s.grade);
			
			printf("\n\n\t\t\t\t\tENTER THE NER RECORD\n\n");
			fflush(stdin);
			printf("\t\tEnter Updated Roll number:");
			scanf("%d",&s.roll);
			printf("\t\tEnter Updated Student Name:");
			gets(s.name);
			printf("\t\tEnter Updated Student Section:");
			gets(s.sec);
			printf("\t\tEnter Updated Student Total Marks:");
			scanf("%d",&s.marks);
			printf("\t\tEnter updated Student Grade:");
			scanf("%d",&s.grade);
			fseek(fp,-(long)sizeof(s),1);
			fwrite(&s,sizeof(s),1,fp);
		    printf("\n\n\t\t\t\tRECORD UPDATED SUCCESSFULLY\n\n"); 
		}
	}
	
	if(flag==0)
	{
		printf("\t\t\tSEARCH RECORD CAN NOT FOUND\n\n");
	}
	fclose(fp);
}

void sort_record()
{
	struct student temp;
	struct student arr[50];
	
	int i,j,k=0;
	FILE *fp;
	fp=fopen("stu.txt","rb");
	if(fp==NULL)
	{
		printf("\nFile doesnot exists\n");
		return;	
	}
	
	i=0;
	
	while(fread(&arr[i],sizeof(arr[i]),1,fp)==1)
	{
		i++;
		k++;
	}
	for(i=0;i<k;i++)
	{
		for(j=0;j<k-i-1;j++)
		{
			if(arr[j].roll>arr[j+1].roll)
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
	
	printf("\n\n\t\t\t\t\tAFTER SORTING STUDENT DETAILS\n\n");
	
	for(i=0;i<k;i++)
	{
		printf("\nRoll number \tStudent Name \tSection \tTotal Marks \tGrade \n\n");
		printf("%d\t\t%s\t\t%s\t\t%d\t\t%.2f\n",arr[i].roll,arr[i].name,arr[i].sec,arr[i].marks,arr[i].grade);
		
	}
	
	fclose(fp);
}

