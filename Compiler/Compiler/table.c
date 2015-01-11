#include<string.h>
#include<malloc.h>
#include"getsym.h"
#include"table.h"
#include"error.h"
int tableptr=0;
int ftableptr=0;
struct funtable ftable[20];
struct table symtable[TXMAX];
int inittable()
{
	ftableptr=0;
	tableptr=0;
}
int entertable(int Type,char ID[],int value,float fvalue,int Kind,char fun[])
{
	int debug=0;
	if(check(ID,&debug,fun)!=NOTFOUND)
		error(RE_DECLARATION);
	tableptr++;
	symtable[tableptr].type=Type;
	strcpy(symtable[tableptr].name,ID);//lastID);
	symtable[tableptr].kind=Kind;
	strcpy(symtable[tableptr].area,fun);
	if(Type==CONSTANT)
	{
		symtable[tableptr].length=0;
		switch (Kind)
		{
		case INTTK:
		//	debug++;
			symtable[tableptr].value=value;
			symtable[tableptr].fvalue=fvalue;
			break;
		case CHARTK:
			symtable[tableptr].value=value;
			symtable[tableptr].fvalue=fvalue;
			break;
			//symtable[tableptr].value=num;
		case FLOATTK:
			symtable[tableptr].value=value;
			symtable[tableptr].fvalue=fvalue;
			break;
			default:
				break;
		}
	}
	else if(Type==SIMPLE_VARIABLE)
	{
		symtable[tableptr].value=value;///address
		//symtable
	}
	else if(Type==ARRAY_VARIABLE)
	{
	}
	else if(Type==FUNCTION)
	{
	}
	else if(Type==PARAMETER)
	{
		symtable[tableptr].value=value;
	}
}
int entertablearray(int Type,char ID[],int value,float fvalue,int Kind,char fun[],int length)
{
	int debug=0;
	if(check(ID,&debug,fun)!=NOTFOUND)
		error(RE_DECLARATION);
	tableptr++;
	symtable[tableptr].type=Type;
	strcpy(symtable[tableptr].name,ID);//lastID);
	//symtable[tableptr].name=strcpy(token);///!!
	symtable[tableptr].kind=Kind;
	strcpy(symtable[tableptr].area,fun);
	symtable[tableptr].value=value;//address
	symtable[tableptr].length=length;

}
int entertablefun(int Type,char ID[],int enter,int paranum,int parafirstptr)
{
	int type;
	if(seektable(ID,&type,"static")!=NOTFOUND)
		error(RE_DECLARATION);
	ftableptr++;
	ftable[ftableptr].type=Type;
	ftable[ftableptr].paranum=paranum;
	ftable[ftableptr].enterpnum=enter;
	strcpy(ftable[ftableptr].name,ID);
	ftable[ftableptr].parafirst=parafirstptr;
	return ftableptr;
};
int check(char ID[],int*type, char funID[])
{
	int i;
	for(i=1;i<=ftableptr;i++)
	{
		if(strcmp(ftable[i].name,ID)==0)
		{
			*type=FUNCTION;
			return i;
		}
	}
	for(i=1;i<=tableptr;i++)
	{
		if((strcmp(symtable[i].name,ID)==0)&&((strcmp(symtable[i].area,funID)==0)))
		{
			*type=symtable[i].type;
			return i;
		}
	}
		*type=NOTFOUND;
	return NOTFOUND;
}
int seektable(char ID[],int*type,char funID[])
{
	int i;
	for(i=1;i<=ftableptr;i++)
	{
		if(strcmp(ftable[i].name,ID)==0)
		{
			*type=FUNCTION;
			return i;
		}
	}
	for(i=1;i<=tableptr;i++)
	{
		if((strcmp(symtable[i].name,ID)==0)&&((strcmp(symtable[i].area,funID)==0)))
		{
			*type=symtable[i].type;
			return i;
		}
	}
	for(i=1;i<=tableptr;i++)
	{
		if((strcmp(symtable[i].name,ID)==0)&&(strcmp(symtable[i].area,"static")==0))
		{
			*type=symtable[i].type;
			return i;
		}
	}
	*type=NOTFOUND;
	return NOTFOUND;
}