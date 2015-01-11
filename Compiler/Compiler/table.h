#ifndef TABLE_H
#define TABLE_H
#include "symname.h"
#include "systemconfig.h"
#define COMPARAMETERSNUMBER 10
enum tablename{
	NOTFOUND,
	CONSTANT,
	PARAMETER,
	SIMPLE_VARIABLE,
	ARRAY_VARIABLE,
	FUNCTION
};
struct table
{
	
	int type;//FUNCTION,VARIABLE,CONSTANT
	int kind;//char\int\float
	char name[TOKENLENGTH];
	char area[TOKENLENGTH];//有效函数区域(VARIABLE,CONSTANT)
	float fvalue;
	int value;//常量（char\int）存值，简单变量存函数内地址偏移
	int length;//数组             //、函数长度，参数个数
	//int funparatype[10];

};
struct funtable
{
	int type;//char int float void
	char name[TOKENLENGTH];
	int enterpnum;
	int paranum;
	int parafirst;
	//int funparatype[10];
};
struct arrayinfo
{
	int dim;
	int size;
};
struct functioninfo
{
	int returntype;
	int parameterstype[COMPARAMETERSNUMBER];
	int paranum;

};

int entertablearray(int Type,char ID[],int value,float fvalue,int Kind,char fun[],int length);
int entertable(int Type,char ID[],int value,float fvalue,int Kind,char fun[]);
int seektable(char ID[],int*type,char funID[] );//name,function var...,area

int entertablefun(int Type,char ID[],int enter,int paranum,int parafirstptr);
#endif