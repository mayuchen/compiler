#include"error.h"
#include<string.h>
#include"symname.h"
#include"getsym_private.h"
#include"systemconfig.h"

char token[TOKENLENGTH];
char lastID[TOKENLENGTH];
int tokenptr=0;
char ch;
int num;
float real;
int linenum=0;


int getsym(int*sym)
{    
	int stringflag=0;
	
	cleartoken();
	switch (iswhat(ch))
	{
	case NEWLINEC :readch();linenum++;getsym(sym);break;
	case SPACEC :readch();getsym(sym);break;
	case TABC :readch();getsym(sym);break;
	
	case LETTERC :													 
		while(iswhat(ch)==LETTERC||iswhat(ch)==DIGITC)
		{
			if(!stringflag)
			{
				if(cattoken(ch))
					stringflag=1; 
			}
			readch();
		}
		retract();
		if(stringflag)//tested
			error(STRING_TOO_LONG);
		*sym=reserver();
		if(*sym==IDEN)
			strcpy(lastID,token);
		break;
	case DIGITC:														 
		while (iswhat (ch)==DIGITC)
		{
			cattoken(ch);readch ();
		}
		trannum();
		real=(float)num;
		if(iswhat(ch)==DOTC)							 
		{
			readch();
			if(iswhat(ch)==DIGITC)
				real=tran_demical_part();
		//	else
				//error(WRONG_FORMAT_REAL_NUMBER);
			retract();
			*sym=FLOATCON;
		}
		else
		{
			*sym=INTCON;
			retract();
		}
		break;
	case SINQUOC:
		readch();
		if(ch!='\\')
			num=ch;
		else
		{
			readch();
			switch (ch)
			{
			case 'n':num='\n';break;
			case 't':num='\t';break;
			case '0':num='\0';break;
			case '\'':num='\'';break;
			case '\"':num='\"';break;
			case '\\':num='\\';break;
			case '\?':num='\?';break;
			default:
				break;
			}
		}
		readch();
		if(iswhat(ch)==SINQUOC)
		{
			*sym=CHARCON;
		}
		else
		{
			//////error!!!!!!
			retract();
			retract();
			*sym=QMARK;
		}break;
	case DBLQUOC:   
		do{
			readch();
			if (iswhat(ch)==EOF)
			{
				error(UNFINISHED_STRING);
				*sym=WORDERRORSYM;
				return 1;
			}
			if(!stringflag)
			{
				if(cattoken(ch))
					stringflag=1; 
			}
			if(stringflag) 
				error(STRING_TOO_LONG);
		}while (iswhat(ch)!=DBLQUOC);
		*sym=STRCON;
		break;
	case COLONC:*sym=COLON;break;
	case PLUSC:*sym=PLUS;break;
	case MINUSC:*sym=MINUS;break;
	case STARC:*sym=MULT;break;
	case LPARC:*sym=LPARENT;break;
	case RPARC:*sym=RPARENT;break;
	case LBRACEC:*sym=LBRACE;break;
	case RBRACEC:*sym=RBRACE;break;
	case LBRACKC:*sym=LBRACK;break;
	case RBRACKC:*sym=RBRACK;break;
	case COMMAC:*sym=COMMA;break;
	case SEMIC:*sym=SEMICN;break;
	case DOTC:*sym=PERIOD;break;
	case ENDLC:*sym=EOLINE;break;
	case EOF:*sym=EOFILE;break;
	case EQUC:readch();													
		if(iswhat(ch)==EQUC)
			*sym=EQL;
		else
		{
			retract();
			*sym=ASSIGN;
		}break;
	case EXCLAMC:readch();
		if(iswhat(ch)==EQUC)
			*sym=NEQ;
		else
		{
			retract();
			*sym=WORDERRORSYM;
			error(UNKNOWN_SYMBOL);//undone need non?
		}break;
	case LABRAC:readch();
		if(iswhat(ch)==EQUC)
			*sym=LEQ;
		else
		{
			retract();
			*sym=LSS;
		}break;
	case RABRAC:readch();
		if(iswhat(ch)==EQUC)
			*sym=GEQ;
		else
		{
			retract();
			*sym=GRE;
		}break;
	case DIVIC:readch();
		if(iswhat(ch)==STARC)
		{
			do{
				do{readch();}while(iswhat(ch)!=STARC);
				do{
					readch();
					if(iswhat(ch)==DIVIC)
					{
						*sym=NOTESSYM;
					goto	NEXTSYM;
					}//读入下一字符}
				}while(iswhat(ch)==STARC);
			}while(iswhat(ch)!=STARC);
NEXTSYM:	readch();
			getsym(sym);
		}
		else
		{
			retract();
			*sym=DIV;
		}break;
	default:
		error(UNKNOWN_SYMBOL);
		*sym=WORDERRORSYM;
		break;
	}
	return 0;
};

char readch()
{
	if(ch==EOF)return EOF;
	ch=fgetc(charin);
//	charin++;
	return ch;
};
int cleartoken()
{
	int i;
	for(i=0;i<TOKENLENGTH;i++)
		token[i]='\0';
	tokenptr=0;
	num=0;
	real=0;
	return 0;
};

///////判断char表，更新///////
int iswhat(char c)
{
	if(c<='9'&&c>='0')	return DIGITC;
	if(c<='z'&&c>='a')	return LETTERC;
	if(c<='Z'&&c>='A')	return LETTERC;
	if(c=='_')			return LETTERC;

	if(c=='\t')			return TABC;
	if(c==' ')			return SPACEC ;
	if(c=='\n')			return NEWLINEC;
	
	if(c=='+')			return PLUSC;
	if(c=='-')			return MINUSC;
	if(c=='*')			return STARC;
	if(c=='/')			return DIVIC;
	
	if(c==':')			return COLONC;
	if(c==';')			return SEMIC;
	if(c=='=')			return EQUC;
	if(c=='.')			return DOTC;
	if(c==',')			return COMMAC;
	if(c=='!')			return EXCLAMC;
	
	if(c=='\'')			return SINQUOC;
	if(c=='\"')			return DBLQUOC;
	if(c=='(')			return LPARC;
	if(c==')')			return RPARC;
	if(c=='<')			return LABRAC;
	if(c=='>')			return RABRAC;
	if(c=='{')			return LBRACEC;
	if(c=='}')			return RBRACEC;
	if(c=='[')			return LBRACKC;
	if(c==']')			return RBRACKC;

	if(c==EOF)			return EOF;
	return 0;
};

int cattoken(char c)
{
	if (tokenptr>=TOKENLENGTH-1)
		return 1;
	if(c!='\"')
	token[tokenptr]=c;
	tokenptr ++;
		return 0;
};
int retract()
{
	int origin=ftell(charin);
	fseek(charin,origin-1,0);
	return 0;
};

/////查保留字表，更新/////

int reserver()
{
	if(strcmp(token,"begin")==0)	return BEGINSYM;
	if(strcmp(token,"end")==0)		return ENDSYM;
	if(strcmp(token,"if")==0)		return IFTK;
	if(strcmp(token,"then")==0)		return THENTK;
	if(strcmp(token,"else")==0)		return ELSETK;
	if(strcmp(token,"printf")==0)	return PRINTFTK;
	if(strcmp(token,"scanf")==0)	return SCANFTK;
	if(strcmp(token,"const")==0)	return CONSTTK;
	if(strcmp(token,"int")==0)		return INTTK;
	if(strcmp(token,"float")==0)	return FLOATTK;
	if(strcmp(token,"char")==0)		return CHARTK;
	if(strcmp(token,"do")==0)		return DOTK;
	if(strcmp(token,"while")==0)	return WHILETK;
	if(strcmp(token,"return")==0)	return RETURNTK;
	if(strcmp(token,"void")==0)		return VOIDTK;
	if(strcmp(token,"main")==0)		return MAINTK;
	if(strcmp(token,"switch")==0)	return SWITCHTK;
	if(strcmp(token,"case")==0)		return CASETK;
	if(strcmp(token,"default")==0)	return DEFAULTTK;
	if(strcmp(token,"for")==0)		return FORTK;
	return IDEN;
	//////查保留字表////////
}

/////数字处理/////

int trannum()
{
	int n=0;
	int ptr=0;
	num=0;
	if(token[0]=='0'&&tokenptr>1)
		error(WRONG_FORMAT_INTEGER);
	while(token[ptr]=='0')ptr++;
	///if(tokenptr-ptr>INTEGERLENGTH)error(INTEGER_OVERFLOW);
	for(;ptr<tokenptr;ptr++)
	{
		num=num*10+(token[ptr]-'0');
	}
	return num;
}
float tran_demical_part()
{
	int level=10;
	while (iswhat(ch)==DIGITC)
	{
		real=real+((float)(ch-'0'))/(level);
		level=10*level;
		readch();
	}
	return real;
}
