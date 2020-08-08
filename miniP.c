#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
static appno=13000;
typedef struct Date
{
	int d,m,year;
}Date;
typedef struct Pass
{
	Date d;
	int valid;
}Pass;
typedef struct Applicant
{
	int appno;
	char fname[15];
	char mname[15];
	char lname[15];
	int age;
	char gender[10];
	char address[20];
	Pass p;
}Applicant;
typedef struct Queue
{
	int f,r;
	Applicant *a[MAX];
}Queue;
void init (Queue *q)
{
	q->f=q->r=-1;
}
void getDetails(Applicant *a1)
{
	int g1;
	printf("Enter the details of the applicant:\n");
	printf("Enter full name:(FIRST NAME      MIDDLE NAME      SURNAME)");
	scanf("%s %s %s",a1->fname,a1->mname,a1->lname);
	printf("Enter age:");
	scanf("%d",&(a1->age));
	printf("Enter nearest station:");
	scanf("%s",a1->address);
	printf("Enter gender(1 or 2):1.MALE\t2.FEMALE");
	scanf("%d",&g1);
	while (g1!=1&&g1!=2)
	{
		printf("Enter valid option.\n");
		scanf("%d",&g1);
	}
	if (g1==1)
		strcpy(a1->gender,"MALE");
	else
		strcpy(a1->gender,"FEMALE");
	do
	{
		printf("Enter DATE of beginning for the pass:(dd/mm/yyyy)");
		scanf("%d/%d/%d",&a1->p.d.d,&a1->p.d.m,&a1->p.d.year);
	}while(a1->p.d.m>12||a1->p.d.d>31);
	printf("Enter validity:(No. of months)");
	scanf("%d",&a1->p.valid);

}
int addApplicant(Queue *q)
{
	if (q->f==-1&&q->r==9)
	return -1;
	else if (q->f==-1)
	q->f=q->r=0;
	else
	q->r++;
	Applicant *new =(Applicant *)(malloc(sizeof(Applicant)));
	q->a[q->r]=new;
	getDetails(q->a[q->r]);
	return q->a[q->r]->appno=++appno;
}
int search(Queue *q,int v)
{
	int i;
	for (i=q->f;i<=q->r;i++)
	{
		if (q->a[i]->appno==v)
			return i;
	}
	return -1;
}
int status(Queue*q,int appno)
{
	int index=search(q,appno);
	if (index==-1)
	{
		printf("APPLICATION NO. %d DOES NOT EXIST.\nPLEASE ENTER A VALID APPLICATION NO. AND TRY AGAIN",appno);
		return -1;
	}
	else if (index==q->f)
	{	
		printf("APPLICATION NO.: %d\tSTATUS: READY");
		return 1;
	}
	else
	{
		printf("APPLICATION NO.: %d \tSTATUS:NOT READY",appno);
		return 0;
	}
}
void printForm(Queue *q,int appno)
{ 
	if (search(q,appno)==-1)
	{
		printf("APPLICATION NO. %d DOES NOT EXIST.\nPLEASE ENTER A VALID APPLICATION NO. AND TRY AGAIN",appno);
	}
	else if (q->a[q->f]->appno==appno)
	{
		printf("--------------------------------------------------------------------------------------------------------------------\nCONCESSION FORM\n\n");
		printf("NAME: %s %s %s\nAGE: %d\nGENDER: %s\nFROM: %s\tTO: Bandra\nVALIDITY FROM: %d/%d/%d FOR %d MONTHS\n",q->a[q->f]->fname,q->a[q->f]->mname,q->a[q->f]->lname,q->a[q->f]->age,q->a[q->f]->gender,q->a[q->f]->address,q->a[q->f]->p.d.d,q->a[q->f]->p.d.m,q->a[q->f]->p.d.year,q->a[q->f]->p.valid);
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		q->f++;
	}
	else
	{
		printf("CANNOT PRINT FORM AS IT IS NOT READY\nTRY AGAIN LATER");
	}
}
int main ()
{
	Queue q;
	init(&q);
	int opt;
	int i,appno;
	do
	{
		printf("\nSELECT AN OPTION FROM BELOW:\n1.Apply for Concession\n2.Check Status\n3.Print form\n4.Exit\n");
		scanf ("%d",&opt);
		switch(opt)
		{
			case 1:	i=addApplicant(&q);
					if (i==-1)
					printf("CANNOT ACCEPT APPLICATION RIGHT NOW.\nPLEASE TRY AGAIN LATER\nTHANK YOU.");
					else
					printf("APPLICATION SUCCESSFUL.\nYour Application number is: %d",q.a[q.r]->appno);
					break;
			case 2: printf("Enter application no.:");
					scanf("%d",&appno);
					status(&q,appno);
					break;
			case 3: printf("Enter application no.");
					scanf("%d",&appno);
					printForm(&q,appno);
					break;
			case 4: printf("\n\nTHANK YOU.");
					break;
			default: printf("Enter valid option.");
		}
		printf("\n\n");
	}while(opt!=4);
}
