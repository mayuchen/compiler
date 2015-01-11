#include"getsym.h"
#include"error.h"
#include"table.h"
#include"syntax.h"
#include"gencode.h"
#include<malloc.h>
#include<stdio.h>
#include<string.h>
extern FILE* charin;
extern char string[][TOKENLENGTH];
extern int stringptr;
extern int linenum;
extern int plast;
extern int tableptr;
extern struct PCODE Pcodes[];
extern struct funtable ftable[];
extern struct table symtable[];
extern struct funtable ftable[];
int fptrmark=0;//ftell(charin);
int lptrmark=0;//linenum;
int test(int *sym,char s1[],char s2[],int errn)
{
	int i;
	int s1size=strlen(s1);
	int s2size=strlen(s2);
	for(i=0;i<s1size;i++)
		if(s1[i]==(*sym))
			return 1;
	error(errn);
	while(1)
	{
		for(i=0;i<s2size;i++)
			if(s2[i]==(*sym))
				return 0;
		readch();
		getsym(sym);
	}
	return 0;
}

int constdeclaration(int *sym,char area[])
{
	/*char declarfsym[]={CHARTK,FLOATTK,INTTK,'\0'};
	char sentencend[]={SEMICN,COMMA,EOFILE,'\0'};
	char endline[]={SEMICN,EOFILE,'\0'};*/
	int type;
	char fun[TOKENLENGTH];
	char declarfsym[]={INTTK,CHARTK,FLOATTK,'\0'};
	char sentenceend[]={SEMICN,CONSTTK,INTTK,FLOATTK,CHARTK,VOIDTK,
		RBRACE,IFTK,DOTK,FORTK,LBRACE,RETURNTK,PRINTFTK,SCANFTK,'\0'};
	strcpy(fun,area);
	
	readch();getsym(sym);
	type=*sym;
	if(!test(sym,declarfsym,sentenceend,DECLARATION_IS_NOT_START_WITH_TYPE))//没有使用类型标示符，跳到下一句开始处
	{
		readch();getsym(sym);
		return DECLARATION_IS_NOT_START_WITH_TYPE;
	}
	do{
		char name[TOKENLENGTH];
		char Id[]={IDEN,'\0'};
		char eql[]={ASSIGN,'\0'};
		char Int[]={INTCON,'\0'};
		char ff[]={INTCON,FLOATCON,'\0'};
		char ch2[]={CHARCON,'\0'};
		char CommaSemicn[]={COMMA,SEMICN,CONSTTK,INTTK,FLOATTK,CHARTK,VOIDTK,
			RBRACE,IFTK,DOTK,FORTK,LBRACE,RETURNTK,PRINTFTK,SCANFTK,'\0'};
		/////const  int/char/float
		readch();getsym(sym);
		if(!test(sym,Id,CommaSemicn,DECLARATION_SHOULD_HAVE_A_ID))///没有标识符，跳到逗号或下一句
			if(*sym==COMMA)//逗号时继续常量声明
				continue;
			else
			{
		//		readch();getsym(sym);//////nextlinefirstsymbol
				return DECLARATION_SHOULD_HAVE_A_ID;////下一句时返回（因为调用时外面有while==SEMICN继续读）
			}
		strcpy(name,token);
		/////const  int a
		readch();
		getsym(sym);//EQL
		if(!test(sym,eql,CommaSemicn,DECLARATION_HAVE_NO_EQL))
			if(*sym==COMMA)
				continue;
			else
				{
					//readch();getsym(sym);
					return DECLARATION_HAVE_NO_EQL;
				}
					///const int a=
		switch (type)
		{
		case INTTK:
			readch();getsym(sym);
			if(*sym==MINUS)
			{
				readch();getsym(sym);
				num=-num;
				real=-real;
			}
			else if(*sym==PLUS)
			{
				readch();
				getsym(sym);
			}
			if(!test(sym,Int,CommaSemicn,ERROR_DATA_TYPE))
				if(*sym==COMMA)
					continue;
				else
				{
					return ERROR_DATA_TYPE;
				}
			entertable(CONSTANT,name,num,real,INTTK,fun);
			break;
		case CHARTK:
			readch();getsym(sym);
			if(!test(sym,ch2,CommaSemicn,ERROR_DATA_TYPE))
				if(*sym==COMMA)
					continue;
				else
				{
					return ERROR_DATA_TYPE;
				}
			entertable(CONSTANT,name,num,real,CHARTK,fun);break;
		case FLOATTK:
			readch();getsym(sym);
			if(*sym==MINUS)
			{
				readch();getsym(sym);
				num=-num;
				real=-real;
			}//sym==PLUS
			if(!test(sym,ff,CommaSemicn,ERROR_DATA_TYPE))
				if(*sym==COMMA)
					continue;
				else
				{
					return ERROR_DATA_TYPE;
				}
			entertable(CONSTANT,name,num,real,FLOATTK,fun);break;
		default:
			break;
		}
		readch();getsym(sym);
		
	}while (*sym==COMMA);
	fptrmark=ftell(charin);lptrmark=linenum;
	if(*sym!=SEMICN)
		error(MISSING_SEMICN);
	else
	{
		
		
		readch();getsym(sym);
	}
	return NO_ERROR;

}
///错误处理完成 已测试
int vardeclaration(int *sym,char area[],int *addr)
{
	/*char declarfsym[]={CHARTK,FLOATTK,INTTK,'\0'};
	char sentencend[]={SEMICN,EOFILE,'\0'};*/
	char endone[]={COMMA,SEMICN,'\0'};
	char id[]={IDEN,'\0'};
	char sentenceend[]={SEMICN,CONSTTK,INTTK,FLOATTK,CHARTK,VOIDTK,
		RBRACE,IFTK,DOTK,FORTK,LBRACE,RETURNTK,PRINTFTK,SCANFTK,'\0'};
	char CommaSemicn[]={COMMA,SEMICN,CONSTTK,INTTK,FLOATTK,CHARTK,VOIDTK,
		RBRACE,IFTK,DOTK,FORTK,LBRACE,RETURNTK,PRINTFTK,SCANFTK,'\0'};
	char name[TOKENLENGTH];
	int type=*sym;
	char fun[TOKENLENGTH];
	strcpy(fun,area);

	do{
		readch();getsym(sym);
		if(!test(sym,id,CommaSemicn,DECLARATION_SHOULD_HAVE_A_ID))
			if(*sym==COMMA)
				continue;
			else
				return DECLARATION_SHOULD_HAVE_A_ID;
		strcpy(name,token);
		readch();getsym(sym);
		if(*sym!=LBRACK)///简单变量,错误处理已测试
		{
			if(!test(sym,endone,CommaSemicn,ERROR_VARIABLEDELARTION))
				if(*sym==COMMA)
					continue;
				else
					return DECLARATION_SHOULD_HAVE_A_ID;
			entertable(SIMPLE_VARIABLE,name,*addr,0,type,fun);
			if((strcmp(fun,"static")!=0))
				switch (type)
				{
				case INTTK:
					gencodei(INT,I,1);
					break;
				case CHARTK:
					gencodei(INT,C,1);
					break;
				case FLOATTK:
					gencodei(INT,F,1);
					break;
				default:
					gencodei(INT,NO,1);
					break;
				}
			else
			{
				switch (type)
				{
				case INTTK:
					gencodei(GINT,I,1);
					break;
				case CHARTK:
					gencodei(GINT,C,1);
					break;
				case FLOATTK:
					gencodei(GINT,F,1);
					break;
				default:
					gencodei(GINT,NO,1);
					break;
				}
			}

			
			(*addr)++;
		//	fptrmark=ftell(charin);
		//	lptrmark=linenum;
		//	readch();getsym(sym);
		}
		else//array
		{
			char INT2[]={INTCON,'\0'};
			char RB[]={RBRACK,'\0'};
			readch();getsym(sym);
			if(!test(sym,INT2,CommaSemicn,ERROR_VARIABLEDELARTION))
				if(*sym==COMMA)
					continue;
				else
					return ERROR_VARIABLEDELARTION;
			if(num<=0)
				error(ERROR_VARIABLEDELARTION);
			entertablearray(ARRAY_VARIABLE,name,*addr,0,type,fun,num);///////entertablearray
			(*addr)=*addr+num;
			if((strcmp(fun,"static")!=0))
				switch (type)
				{
				case INTTK:
					gencodei(INT,I,num);
					break;
				case CHARTK:
					gencodei(INT,C,num);
					break;
				case FLOATTK:
					gencodei(INT,F,num);
					break;
				default:
					gencodei(INT,NO,num);
					break;
				}
			else
				switch (type)
				{
				case INTTK:
					gencodei(GINT,I,num);
					break;
				case CHARTK:
					gencodei(GINT,C,num);
					break;
				case FLOATTK:
					gencodei(GINT,F,num);
					break;
				default:
					gencodei(GINT,NO,num);
					break;
				}
			readch();getsym(sym);
			if(!test(sym,RB,CommaSemicn,ERROR_VARIABLEDELARTION))
				if(*sym==COMMA)
					continue;
				else
					return ERROR_VARIABLEDELARTION;
			readch();getsym(sym);
		}
		//////////////////////////////////////////array
		;
	}while(*sym==COMMA);
	if(*sym!=SEMICN)
		error(MISSING_SEMICN);
	else
	{
		fptrmark=ftell(charin);
		lptrmark=linenum;
		readch();getsym(sym);
	}
}//已测试

int expression(int *sym,char FunID[])
{
	int pm=0;/////////////////////////////////////////////////////////////////////////////////////////////
	if(*sym==PLUS||*sym==MINUS)
	{
		pm=*sym;
		readch();getsym(sym);
	}
	term(sym,FunID);
	if(pm==MINUS)
		gencodei(OPR,0,OPP);
	//pm=*sym;
	//readch();getsym(sym);
	while(*sym==PLUS||*sym==MINUS)
	{
		int am=*sym;
		readch();getsym(sym);
		term(sym,FunID);
		if(am==PLUS)
			gencodei(OPR,0,ADD);
		else
			gencodei(OPR,0,MNS);
	}
}
int term(int *sym,char FunID[])
{
	factor(sym,FunID);
	//readch();getsym(sym);
	while(*sym==MULT||*sym==DIV)
	{
		int td=*sym;
		readch();getsym(sym);
		factor(sym,FunID);
		if(td==MULT)
			gencodei(OPR,0,MUL);
		else
			gencodei(OPR,0,DIVI);
	}
}
int factor(int *sym,char FunID[])
{
	int type;
	int pptr;
	int pm=PLUS;
start:	switch (*sym)
	{
	case PLUS:
	case MINUS:
		pm=*sym;
		readch();getsym(sym);
		if(*sym!=INTCON)
			error(WRONG_EXPRESSION);
		goto start;
		break;
	case INTCON:
		if(pm==MINUS)
			num=-num;
		gencodei(LIT,I,num);
		readch();
		getsym(sym);
		break;
	case CHARCON:
		gencodei(LITC,C,num);
		readch();
		getsym(sym);
		break;
	case FLOATCON:
		if(pm==MINUS)
			real=-real;
		gencodef(LITF,0,real);
		readch();//负数？expression已经考虑？
		getsym(sym);
		break;
	case IDEN:
		pptr=seektable(token,&type,FunID);
		switch (type)
		{
		case CONSTANT:
			if(symtable[pptr].kind==FLOATTK)
				gencodef(LITF,0,symtable[pptr].fvalue);
			else if((symtable[pptr].kind==INTTK))
				gencodei(LIT,I,symtable[pptr].value);
			else if (symtable[pptr].kind==CHARTK)
				gencodei(LITC,C,symtable[pptr].value);
			readch();
			getsym(sym);
			break;
		case SIMPLE_VARIABLE:
				gencodei(LOD,(strcmp(symtable[pptr].area ,"static")==0?3:1),symtable[pptr].value+2);//段内偏移立即数
				readch();
				getsym(sym);
				break;
		case PARAMETER:
			{
				int ftype;
				int fptr=seektable(FunID,&ftype,"static");
				gencodei(LOD,1,symtable[pptr].value-ftable[fptr].paranum);
				readch();
				getsym(sym);
			}
			break;
		case ARRAY_VARIABLE:
			if(strcmp(symtable[pptr].area,"static")==0)
				gencodei(LIT,0,symtable[pptr].value+2);////全局数组先取首地址
			else 
				gencodei(LIT,0,symtable[pptr].value+2);////局部数组首地址
			readch();getsym(sym);					   ////读取[
			readch();getsym(sym);					   ////读取整型数或表达式
			expression(sym,FunID);					   ////
			gencodei(OPR,0,ADD);					   ////加得偏移
			if(strcmp(symtable[pptr].area,"static")==0)
				gencodei(LOD,2,0);
			else
				gencodei(LOD,0,0);
			readch();
			getsym(sym);
			break;
		case FUNCTION:
			if(ftable[pptr].type==VOIDTK)
				error(WRONG_EXPRESSION);
			{
				cal_function(sym,FunID);
				if(ftable[pptr].type==INTTK)
					gencodei(OPR,I,LRS);
				else
					gencodei(OPR,C,LRS);
			}		
				break;
			break;
		case NOTFOUND:
			error(USING_AN_ICON_WITHOUT_DECLARTION);
			while(*sym!=SEMICN&&*sym!=RBRACE&&*sym!=RPARENT&&*sym!=COMMA
				&&*sym!=PLUS&&*sym!=MINUS&&*sym!=MULT&&*sym!=DIV)
			{readch();
			getsym(sym);}
			break;
		default:
			break;
		}
		break;
	case LPARENT:
		readch();getsym(sym);
		expression(sym,FunID);
		readch();getsym(sym);
		break;
	default:
		error(WRONG_EXPRESSION);
		///////term错误的入口项////
		break;
	}
}
int cal_function(int *sym,char funID[])
{
	int tmp;
	int fptr=seektable(token,&tmp,"static");
	//int parafirst=fptr+1;//??
	int paranum=ftable[fptr].paranum;
	int i;
	//gencodei(INT,0,2);
	
	readch();getsym(sym);//LP
	readch();getsym(sym);
	for(i=0;i<paranum;i++)
	{
		expression(sym,funID);
		if(*sym==COMMA)
		{
			readch();getsym(sym);
			continue;
		}
		else if(*sym==RPARENT)
		{
			if(i+1!=paranum)
			{
				//error
				readch();getsym(sym);
				return -1;
			}
		}
	}
	if(*sym==RPARENT)
	{
		readch();getsym(sym);
		//gencodei(INT,0,-(paranum+2));
		gencodei(CAL,0,ftable[fptr].enterpnum);
		gencodei(INT,0,-paranum);
		/////****返回值是否压栈？不能压栈
		return 0;
	}
	else
	{
		return -1;
	}
	////error
}

int sentence(int *sym,char name[])
{
	switch(*sym)
	{
		case EOFILE:error(TOO_MANY＿CODE_AFTER_MAIN_FUNCTION);//??wrong structure?
		case IFTK:if_sentence(sym,name); break;//tested
		case FORTK:for_sentence(sym,name); break;//tested
		case DOTK:do_sentence(sym,name);break;//tested
			
		case IDEN:
		{
			int funorvar;
			int addr;
			addr=seektable(token,&funorvar,name);
			if(funorvar==FUNCTION)
			{
				cal_function(sym,name);
				readch();getsym(sym);
			}
			else if(funorvar==SIMPLE_VARIABLE||funorvar==ARRAY_VARIABLE||funorvar==PARAMETER)
			{
				assign_sentence(sym,name);
			}
				
			else
			{
				error(USING_AN_ICON_WITHOUT_DECLARTION);
				while(*sym!=SEMICN)
				{readch();getsym(sym);}
				readch();getsym(sym);
			}
			break;
		}
		case RETURNTK:
			return_sentence(sym,name);break;
		case PRINTFTK:
			write(sym,name);
			break;
		case SCANFTK:
			read(sym,name);
			break;

		case LBRACE:
			readch();getsym(sym);
			do{
				sentence(sym,name);
			}while(*sym!=RBRACE&&*sym!=EOFILE);
			if(*sym==EOFILE)
				error(TOO_MANY＿CODE_AFTER_MAIN_FUNCTION);
			readch();getsym(sym);
				break;//sentences(sym,name);break;
		case RBRACE:
				return NO_ERROR;
				break;
		case SEMICN:
			readch();getsym(sym);
			break;
		default:
			error(ERROR_SENTENCE);
			while ((*sym!=SEMICN)&&(*sym!=RBRACE)&&(*sym!=EOFILE))
			{
				readch();getsym(sym);
			}
			if(*sym==SEMICN)
			{readch();getsym(sym);}
			break;	//错误处理
		}
	
	//readch();getsym(sym);
}

int function_body(int *sym,char name[],int funptr)
{
	//{
	int varaddr;
	readch();getsym(sym);
	while(*sym==CONSTTK)
	{
		constdeclaration(sym,name);
		while (*sym==SEMICN)
		{
			readch();getsym(sym);
		}
	}
	varaddr=0;
	while(*sym==INTTK||*sym==CHARTK||*sym==FLOATTK)
	{
		vardeclaration(sym,name,&varaddr);
		while (*sym==SEMICN)
		{
			readch();getsym(sym);
		}
	}
	while(*sym!=RBRACE&&*sym!=EOFILE)
	{
		sentence(sym,name);
	}
	if(*sym!=RBRACE)
		error(UNFINISHED_PROGRAM);
	gencodei(OPR,0,RET);
	readch();getsym(sym);
}

int read(int *sym,char funid[])
{
	////scanf
	//char idname[TOKENLENGTH];
	int flag=1;
	readch();getsym(sym);
	do{
		readch();
		getsym(sym);
		if(*sym==IDEN)
		{
			int type;
			int tableaddr=seektable(token,&type,funid);
			if(type==SIMPLE_VARIABLE)
			{
				switch (symtable[tableaddr].kind)
				{
				case INTTK:
					gencodei(REDI,0,0);
					break;
				case CHARTK:
					gencodei(REDC,0,0);
					break;
				case FLOATTK:
					gencodei(REDF,0,0);
					break;
				default:
					break;
				}
			
			if(strcmp(symtable[tableaddr].area,"static")==0)
			{
				gencodei(STO,3,symtable[tableaddr].value+2);
			}
			else if(strcmp(symtable[tableaddr].area,funid)==0)
				gencodei(STO,1,symtable[tableaddr].value+2);
			else
				error(ERROR_IN_READ_SENTENCE);///error;
			}
			else if(type==ARRAY_VARIABLE)
			{
				int ptest;
				readch();getsym(sym);
				readch();getsym(sym);
				ptest=plast;
				expression(sym,funid);
				///////////此应判断是否为简单整数且越界//////////////////
				if((plast==ptest+1)&&(Pcodes[plast-1].codename==LIT))
				if(Pcodes[plast-1].i>=symtable[tableaddr].length)
					error(ARRAY_OVERFLOW);
				if((plast==ptest+1)&&(Pcodes[plast-1].codename==LIT)&&(Pcodes[plast-1].l==F))
					error(ARRAY_SUBVALUE_SHOULD_BE_INTEGER);
				/*************************已完成******************************/
				gencodei(LIT,0,symtable[tableaddr].value+2);
				gencodei(OPR,0,ADD);
				switch (symtable[tableaddr].kind)
				{
				case INTTK:
					gencodei(REDI,0,0);
					break;
				case CHARTK:
					gencodei(REDC,0,0);
					break;
				case FLOATTK:
					gencodei(REDF,0,0);
					break;
				default:
					break;
				}
				if(strcmp(symtable[tableaddr].area,"static")==0)
				{
					gencodei(STO,2,symtable[tableaddr].value+2);
				}
				else if(strcmp(symtable[tableaddr].area,funid)==0)
					gencodei(STO,0,symtable[tableaddr].value+2);
				//readch();getsym(sym);
			}
			else if(type=PARAMETER)
			{
				int ftype;
				int fptr=seektable(funid,&ftype,"static");
				switch (symtable[tableaddr].kind)
				{
				case INTTK:
					gencodei(REDI,0,0);
					break;
				case CHARTK:
					gencodei(REDC,0,0);
					break;
				case FLOATTK:
					gencodei(REDF,0,0);
					break;
				default:
					break;
				}
				gencodei(STO,1,symtable[tableaddr].value-ftable[fptr].paranum);	
			}
			readch();getsym(sym);
		}
		else///error
		{

		}
	}while(*sym==COMMA);
	if(*sym!=RPARENT)
	{
		error(ERROR_IN_READ_SENTENCE);///error
		flag=0;	
	}
	if(flag==1)
	{readch();getsym(sym);}
	if(*sym!=SEMICN)
	{
		error(MISSING_SEMICN);return -1;
	}
	readch();getsym(sym);
}
int write(int *sym,char funid[])
{
	int flag=1;
	readch();getsym(sym);
	readch();getsym(sym);
	if(*sym==STRCON)
	{
		strcpy(string[stringptr],token);
		gencodei(WRTS,0,stringptr);
		stringptr++;
		readch();getsym(sym);
	}
	else
	{
		expression(sym,funid);
		gencodei(WRT,0,0);
			
	}


	while(*sym!=RPARENT)
	{
		if(*sym==COMMA)
		{
			readch();getsym(sym);
			expression(sym,funid);
			gencodei(WRT,0,0);
		}
		else
		{
			error(ERROR_IN_WRITE_SENTENCE);
			flag=0;
			break;
		}
	}
	if(flag==1)
	{readch();getsym(sym);}
	if(*sym!=SEMICN)
	{
		error(MISSING_SEMICN);return -1;
	}
	else
	{
	readch();getsym(sym);
	}	
}
int return_sentence(int *sym,char funID[])
{
//	int funtype;
	int tmp;
	int fid;
	
	
	if(strcmp(funID,"main")==0)
	{
		char se[]={SEMICN,'\0'};
		readch();getsym(sym);/////;
		test(sym,se,se,ERROR_RETURN_TYPE);
		readch();getsym(sym);
		gencodei(JMP,0,0);
		return ;
	}
	fid=seektable(funID,&tmp,funID);


	/*if(strcmp(ftable[fid].name,"main")==0)
		gencodei(JMP,0,0);
	else*/ if(ftable[fid].type==VOIDTK)
	{
		char se[]={SEMICN,'\0'};
		gencodei(OPR,0,RET);
		readch();getsym(sym);
		test(sym,se,se,ERROR_RETURN_TYPE);
	}
	else
	{
		int t;
		readch();getsym(sym);
		if(*sym==SEMICN)
		{
			gencodei(OPR,0,RET);
			readch();getsym(sym);
			error(ERROR_RETURN_TYPE);
			return -1;
		}
		expression(sym,funID);
		if(ftable[fid].type==INTTK)
			t=I;
		else if(ftable[fid].type==CHARTK)
			t=C;
		else
			t=F;
		gencodei(OPR,t,RTS);
	}
	readch();getsym(sym);/////;
//	readch();getsym(sym);
}
int if_sentence(int *sym,char funid[])
{
	int cmp,elsptr;
	readch();getsym(sym);
	readch();getsym(sym);
	expression(sym,funid);
	cmp=*sym;
	if(cmp!=RPARENT)
	{readch();getsym(sym);
	expression(sym,funid);}
	switch (cmp)
	{
	case GRE:gencodei(OPR,0,BIG);break;
	case LSS:gencodei(OPR,0,SMA);break;
	case GEQ:gencodei(OPR,0,BEQ);break;
	case LEQ:gencodei(OPR,0,SEQ);break;
	case EQL:gencodei(OPR,0,PEQU);break;
	case NEQ:gencodei(OPR,0,PNEQ);break;
	case RPARENT:break;
	default:///error
		break;
	}
	readch();getsym(sym);
	cmp=plast;
	gencodei(JPC,0,0);///回填
	if(*sym!=RBRACE)
		sentence(sym,funid);
	else
		error(MISSING_SENTENCE);
	elsptr=plast;
	gencodei(JMP,0,plast+1);///有else回填
	Pcodes[cmp].i=plast;
	cmp=plast;
	if(*sym==ELSETK)
	{
		readch();getsym(sym);
		sentence(sym,funid);
		Pcodes[elsptr].i=plast;
	}
	else
	{gencodei(NOP,0,0);}
	
}
int assign_sentence(int *sym,char funID[])
{
	int type;
	int addr=seektable(token,&type,funID);
	int ftype;
	int fptr=seektable(funID,&ftype,"static");
	//	int stackadd;
	if(type==PARAMETER)
	{
		readch();getsym(sym);//ASSIGN
		if(*sym!=ASSIGN)
		{
			error(WRONG_ASSIGN_SYNTAX);
			goto ASS_ERROR;
		}
		readch();getsym(sym);
		expression(sym,funID);
		{
			gencodei(STO,1,symtable[addr].value-ftable[fptr].paranum);		
		}
	}
	else if(type==SIMPLE_VARIABLE)
	{
		readch();getsym(sym);//ASSIGN
		if(*sym!=ASSIGN)
		{
			error(WRONG_ASSIGN_SYNTAX);
			goto ASS_ERROR;
		}
		readch();getsym(sym);
		expression(sym,funID);
		gencodei(STO,(strcmp(symtable[addr].area ,"static")==0?3:1),symtable[addr].value+2);///2?
	}
	/*注意，这里简单变量和数组都没有考虑是否是全局,*/
	/*已经考虑!*/
	else if(type==ARRAY_VARIABLE)
	{
		int ptest;
		readch();getsym(sym);//[
		if(*sym!=LBRACK)
		{
			error(WRONG_ASSIGN_SYNTAX);
			goto ASS_ERROR;
		}
		readch();getsym(sym);
		ptest=plast;
		expression(sym,funID);
		///////////此应判断是否为简单整数且越界//////////////////
		if((plast==ptest+1)&&(Pcodes[plast-1].codename==LIT))
			if(Pcodes[plast-1].i>=symtable[addr].length)
				error(ARRAY_OVERFLOW);
		if((plast==ptest+1)&&(Pcodes[plast-1].codename==LIT)&&(Pcodes[plast-1].l==F))
			error(ARRAY_SUBVALUE_SHOULD_BE_INTEGER);
		/*************************已完成******************************/
		gencodei(LIT,0,symtable[addr].value+2);
		gencodei(OPR,0,ADD);
		readch();getsym(sym);//ASS
		if(*sym!=ASSIGN)
		{
			error(WRONG_ASSIGN_SYNTAX);
			goto ASS_ERROR;
		}
		readch();getsym(sym);
		expression(sym,funID);
		gencodei(STO,(strcmp(symtable[addr].area,"static")==0?2:0),0);/////////////////////是否全局？/////////////////////////
	}
	else//NOFOUND
	{
		error(USING_AN_ICON_WITHOUT_DECLARTION);
ASS_ERROR:	while(*sym!=SEMICN||EOFILE)
		{
			readch();getsym(sym);
		}
	}
	if(*sym!=SEMICN)
	{
		error(MISSING_SEMICN);return -1;
	}
	readch();getsym(sym);
}
int for_assign_sentence(int *sym,char funID[])
{
	/*********
	for语句加减步长的子程序，
	但是直接使用了assign的子程序，唯一修改的的结束符号为）
	步长为整数应该改。
	*********/
	int type;
	int addr=seektable(token,&type,funID);
	int ftype;
	int fptr=seektable(funID,&ftype,"static");
	//	int stackadd;
	if(type==PARAMETER)
	{
		readch();getsym(sym);//ASSIGN
		if(*sym!=ASSIGN)
		{
			error(WRONG_ASSIGN_SYNTAX);
			goto ASS_ERROR;
		}
		readch();getsym(sym);
		expression(sym,funID);
		{
			gencodei(STO,1,symtable[addr].value-ftable[fptr].paranum);		
		}
	}
	else if(type==SIMPLE_VARIABLE)
	{
		readch();getsym(sym);//ASSIGN
		if(*sym!=ASSIGN)
		{
			error(WRONG_ASSIGN_SYNTAX);
			goto ASS_ERROR;
		}
		readch();getsym(sym);
		expression(sym,funID);
		gencodei(STO,(strcmp(symtable[addr].area ,"static")==0?3:1),symtable[addr].value+2);///2?
	}
	/*注意，这里简单变量和数组都没有考虑是否是全局,*/
	/*已经考虑!*/
	else if(type==ARRAY_VARIABLE)
	{
		int ptest;
		readch();getsym(sym);//[
		if(*sym!=LBRACK)
		{
			error(WRONG_ASSIGN_SYNTAX);
			goto ASS_ERROR;
		}
		readch();getsym(sym);
		ptest=plast;
		expression(sym,funID);
		///////////此应判断是否为简单整数且越界//////////////////
		if((plast==ptest+3)&&(Pcodes[plast-2].codename==LIT))
			if(Pcodes[plast-2].i>=symtable[addr].length)
				error(ARRAY_OVERFLOW);
		if((plast==ptest+3)&&(Pcodes[plast-2].codename==LIT)&&(Pcodes[plast].l==F))
			error(ARRAY_SUBVALUE_SHOULD_BE_INTEGER);
		/*******************************************************/
		gencodei(LIT,0,symtable[addr].value+2);
		gencodei(OPR,0,ADD);
		readch();getsym(sym);//ASS
		if(*sym!=ASSIGN)
		{
			error(WRONG_ASSIGN_SYNTAX);
			goto ASS_ERROR;
		}
		readch();getsym(sym);
		expression(sym,funID);
		gencodei(STO,(strcmp(symtable[addr].area,"static")==0?2:0),0);/////////////////////是否全局？/////////////////////////
	}
	else//NOFOUND
	{
		error(USING_AN_ICON_WITHOUT_DECLARTION);
ASS_ERROR:	while(*sym!=SEMICN)
		{
			readch();getsym(sym);
		}
	}
	if(*sym!=RPARENT)
	{
		error(PARENT_DISMATCH);return -1;
	}
	readch();getsym(sym);
}
int do_sentence(int *sym,char funid[])
{
	int cmp;
	int pptr=plast;
	readch();getsym(sym);
	sentence(sym,funid);
	///while
	if(*sym!=WHILETK)
	{
		error(MISSING_WHILE);
		return MISSING_WHILE;
	}
	readch();getsym(sym);//LP
	if(*sym!=LPARENT)
	{
		////error
	}
	readch();getsym(sym);
	expression(sym,funid);
	cmp=*sym;
	if(cmp!=RPARENT)
	{readch();getsym(sym);
	expression(sym,funid);}
	switch (cmp)
	{
	case GRE:gencodei(OPR,0,BIG);break;
	case LSS:gencodei(OPR,0,SMA);break;
	case GEQ:gencodei(OPR,0,BEQ);break;
	case LEQ:gencodei(OPR,0,SEQ);break;
	case EQL:gencodei(OPR,0,PEQU);break;
	case NEQ:gencodei(OPR,0,PNEQ);break;
	case RPARENT:break;
	default:///error
		break;
	}
	gencodei(OPR,0,NON);
	gencodei(JPC,0,pptr);
	if(*sym!=RPARENT)
	{
		error(PARENT_DISMATCH);
	}
	else
	{
		readch();getsym(sym);
	}
/*	if(*sym!=SEMICN)
	{
		error(MISSING_SEMICN);return -1;
	}
	readch();getsym(sym);*/
}
int for_sentence(int *sym,char funid[])
{
	int pcondi;
	int pjpc;
	readch();getsym(sym);//LP
	readch();getsym(sym);
	assign_sentence(sym,funid);
	pcondi=plast;
	expression(sym,funid);
	if(*sym!=SEMICN)
	{
		int cmp=*sym;
		if(cmp!=SEMICN)
		{readch();getsym(sym);
		expression(sym,funid);}
		switch (cmp)
		{
		case GRE:gencodei(OPR,0,BIG);break;
		case LSS:gencodei(OPR,0,SMA);break;
		case GEQ:gencodei(OPR,0,BEQ);break;
		case LEQ:gencodei(OPR,0,SEQ);break;
		case EQL:gencodei(OPR,0,PEQU);break;
		case NEQ:gencodei(OPR,0,PNEQ);break;
		case RPARENT:break;
		default:///error
			break;
		}
		gencodei(OPR,0,NON);
		readch();getsym(sym);
	}
	pjpc=plast;
	gencodei(JPC,0,0);
	gencodei(JMP,0,0);//to end 回填
	////////////////
	
	for_assign_sentence(sym,funid);
	/////////
	gencodei(JMP,0,pcondi);
	Pcodes[pjpc].i=plast;
	sentence(sym,funid);
	gencodei(JMP,0,pjpc+2);
	Pcodes[pjpc+1].i=plast;

}
int program()
{

	//int symmark=sym;
	int sym;
	int penter=0;
	int vaddr=0;
	//int staticnum=0;
	char ALL[]="static";
	gencodei(CAL,0,2);
	gencodei(JMP,0,0);
	//gencodei(
	readch();getsym(&sym);
	while (sym==CONSTTK)
	{
			constdeclaration(&sym,ALL);
		{	
		//	fptrmark=ftell(charin);lptrmark=linenum;//symmark=sym;
			while(sym==SEMICN)
			{readch();getsym(&sym);}
		}
	}
	///tested
	//next line first symbol is read;
	while(sym==INTTK||sym==CHARTK||sym==FLOATTK)
	{
		int type=sym;
		/*	char Id[]={IDEN};
		char sentencend[]={SEMICN,EOFILE};*/
		readch();getsym(&sym);
		/*if(sym!=IDEN)
		{
			if(sym==SEMICN)
				error(DECLARATION_SHOULD_HAVE_A_ID);
			test(&sym,sentencend,sentencend,DECLARATION_SHOULD_HAVE_A_ID);	
			if(sym==EOFILE)
			{
				error(UNFINISHED_PROGRAM);
				return UNFINISHED_PROGRAM;
			}
			fptrmark=ftell(charin);lptrmark=linenum;
			readch();getsym(&sym);
			continue;
		}*/
		readch();getsym(&sym);
		if(sym==LPARENT)/////说明变量定义已经结束，开始函数部分
		{
			fseek(charin,fptrmark,0);
			linenum=lptrmark;
			readch();getsym(&sym);
			break;
		}
		else if(sym==SEMICN||sym==COMMA||sym==LBRACK)
		{
			fseek(charin,fptrmark,0);
			linenum=lptrmark;
			readch();getsym(&sym);
			vardeclaration(&sym,ALL,&vaddr);////////应该sym==分号出来
		}
		/*else/////错误处理，跳到哪里？///跳到;
		{
			test(&sym,sentencend,sentencend,MISSING_SEMICN);	
			if(sym==EOFILE)
			{
				error(UNFINISHED_PROGRAM);
				return UNFINISHED_PROGRAM;
			}
		}*/

		while(sym==SEMICN)
		{readch();getsym(&sym);}
	}
	////first symbol has been read
	////跳转到主函数入口
	penter=plast;
	gencodei(JMP,0,0);
	////函数定义
	while(sym==INTTK||sym==CHARTK||sym==FLOATTK||sym==VOIDTK)
	{
		char name[TOKENLENGTH];
		/*char declearstart[]={INTTK,CHARTK,FLOATTK,VOIDTK,'\0'};
		char id[]={IDEN,'\0'};
		char vo[]={LBRACE,'\0'};*/
		//int lbsnum=0;
		int funtype=sym;
		int fid;
		if(sym==VOIDTK)
		{
			readch();getsym(&sym);
			if(sym==MAINTK)//主函数出口
				break;
			else
				{
					/*if(!test(&sym,id,vo,ERROR_FUNCTIONDELARATION))
						goto Function_err;*/	
					strcpy(name,token);
			}
		}
		else
		{
			readch();getsym(&sym);
			strcpy(name,token);
			/*if(!test(&sym,id,vo,ERROR_FUNCTIONDELARATION))
				goto Function_err;*/

		}
		readch();getsym(&sym);
		/*{
			char Lp[]={LPARENT,'\0'};
			if(!test(&sym,Lp,vo,ERROR_FUNCTIONDELARATION))
				goto Function_err;
			
		}*/
		
		{
			int paranum=0;
			int paraadd=0;
			int parastart=tableptr+1;
			//char declearpara[]={INTTK,CHARTK,FLOATTK,'\0'};
			
			
			while((sym==LPARENT)||(sym==COMMA))
			{
				int paratype;
//				char paraname[TOKENLENGTH];
				int f=((sym==LPARENT)?1:0);
				readch();getsym(&sym);
				if((sym==RPARENT)&&(f==1))
					break;
				/*if(!test(&sym,declearpara,vo,ERROR_FUNCTIONDELARATION))
					goto Function_err;*/
				paratype=sym;
				readch();getsym(&sym);
				entertable(PARAMETER,token,paranum,0,paratype,name);
				paranum++;
				readch();getsym(&sym);
			}
			fid=entertablefun(funtype,name,plast,paranum,parastart);
		//	gencodei(INT,0,paranum);////?删除
		}
		readch();getsym(&sym);
		function_body(&sym,name,fid);
		//body//
		/*continue;
		Function_err:*/
	}
	Pcodes[penter].i=plast;
	if(sym!=MAINTK)
	{
		error(ERROR_PROGRAM_STRUCTURE);
		while(sym!=MAINTK)
		{
			readch();
			getsym(&sym);
		}
	}
	////main
	readch();getsym(&sym);//LP
	readch();getsym(&sym);//RP
	readch();getsym(&sym);
	function_body(&sym,"main",entertablefun(VOIDTK,"main",plast,0,tableptr+1));
	
	if(sym!=EOFILE)
		error(TOO_MANY＿CODE_AFTER_MAIN_FUNCTION);
	gencodei(OPR,0,RET);
	

}