#include<stdio.h>
#include<string.h>
#include"getsym.h"
#define PROGRAMLENGTH 200
#include"pcodename.h"
#define PCODENUMBER 4000
#include"syntax.h"
FILE* charin;
FILE* err;
struct PCODE Pcodes[PCODENUMBER];
extern int errnum;
int interpret();

void main()
{
	char file[500];
	printf("please input the c0 file dictionary:\n");
	scanf("%s",file);
	
	charin=fopen(file,"r");

//	charin=fopen("code.txt","r");

	err=stdout;//fopen("errinfo.txt","w+");
	program();
	if(errnum==0)
	{
		printf("no error!\n");
		interpret();}
	/***********************词法分析测试***********************已通过***************************
	int sym=0,codelinesnum=0;
	char ch;
	charin=fopen("code.txt","r");
	err=fopen("errinfo.txt","w+");
	do
	{
		readch();
		getsym(&sym);
		printf("%d\n",sym);
	} while (sym!=EOFILE);
	printf ("%d",errnum);
	fclose(err);
	fclose(charin);
	**/
}