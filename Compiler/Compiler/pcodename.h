#ifndef PCODE_NAME_H
#define PCODE_NAME_H
#include"symname.h"
struct PCODE{
	int codename,l;
	int i;
	float f;
};
typedef struct comdata
{
	int type,i;
	float f;
}DATA;
enum datatype
{
	NO,I,F,C
};
enum Pcodenames
{
	LIT=1,LITC,LITF,LODS,LODSI,LOD,LODI,CAL,
	JMP,REDI,OPR,STO,STOI,INT,GINT,JPC,
	WRT,WRTS,REDC,REDF,NOP
};
enum OPRnames
{
	RET,RTS,LRS,OPP,ADD,MNS,MUL,DIVI,PEQU,PNEQ,BIG,BEQ,SMA,SEQ,NON
};
#endif