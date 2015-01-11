#include<stdio.h>
#include"pcodename.h"
FILE*codeout;
extern struct PCODE Pcodes[];
int plast=0;
int gencodef(int codetype,int T1,float f)
{
	
	
	if(Pcodes[plast].codename!=0)
		return 1;
	Pcodes[plast].codename=codetype;
	Pcodes[plast].l=T1;
	Pcodes[plast].i=0;
	Pcodes[plast].f=f;
	plast++;
	return 0;
};
int gencodei(int codetype,int T1,int T2)
{
	//struct PCODE order=Pcodes[plast];
	
	if(Pcodes[plast].codename!=0)
		return 1;
	Pcodes[plast].codename=codetype;
	Pcodes[plast].l=T1;
	Pcodes[plast].i=T2;
	Pcodes[plast].f=T2;
	plast++;
	return 0;
};
int makepcode(struct PCODE pcodes,int codenum)
{
	switch (pcodes.codename)
	{
	case LIT:fprintf(codeout,"%s %d %d");
	default:
		return -1;
		break;
	}
	return 0;
}