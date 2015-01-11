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
	char area[TOKENLENGTH];//��Ч��������(VARIABLE,CONSTANT)
	float fvalue;
	int value;//������char\int����ֵ���򵥱����溯���ڵ�ַƫ��
	int length;//����             //���������ȣ���������
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