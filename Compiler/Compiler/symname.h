#ifndef _SYMNAME_H
#define _SYMNAME_H

enum symbol{
	EOFILE=-1,//程序结束
	WORDERRORSYM,
	


	BEGINSYM=10,
	ENDSYM,
	IFTK,	//if
	THENTK,
	ELSETK,//else
	DOTK,//do
	WHILETK,//while
	SWITCHTK,
	CASETK,
	DEFAULTTK,
	FORTK,
	RETURNTK,//return
	SCANFTK,//scanf
	PRINTFTK,//printf
	MAINTK,//
	CONSTTK,//const
	NOTESSYM,//注释
	INTTK,//int
	FLOATTK,//float
	CHARTK,//char
	VOIDTK,
	IDEN,//（非保留字串）
	INTCON,//整型
	FLOATCON,//浮点型
	CHARCON,
	STRCON,
	SPACE ,//空格回车制表 36
	PLUS ,//加法运算符 
	MINUS ,//减法运算符
	MULT ,//星号
	DIV ,//除号
	LPARENT ,//左括号
	RPARENT ,//右括号
	LBRACE ,//左花括号
	RBRACE ,//右花括号
	LBRACK,
	RBRACK,//方括号 46
	COMMA ,//逗号
	SEMICN ,//分号
	COLON ,//冒号
	ASSIGN ,//赋值运算
	EQL ,//等判断
	GRE ,//大于号 52
	GEQ,//大于等于
	LSS,//小于号
	LEQ,//小于等于
	NEQ,//不等于号
	PERIOD,//点
	QMARK,
	DQMARK,//59
	
	EOLINE//一行代码结束
};
enum charsymbol{
	DOTC=1,//点
	SINQUOC,//单引号
	DBLQUOC,//双引号
	SPACEC,//空格
	TABC,//制表
	NEWLINEC,//回车
	DIGITC,//数字
	LETTERC,//字母
	COLONC,//冒号
	EQUC,//等号
	PLUSC,//加号
	MINUSC,//减号
	EXCLAMC,//叹号
	STARC,//星号
	LPARC,//左小括号
	RPARC,//右小括号
	COMMAC,//逗号
	SEMIC,//分号
	DIVIC,//斜杠
	LBRACEC,//左花括号
	RBRACEC,//右花括号
	LABRAC,//左尖括号
	RABRAC,//右尖括号
	LBRACKC,
	RBRACKC,
	ENDLC// \0
};
//int declarfsym[]={CHARTK,FLOATTK,INTTK};
//int sentencend[]={SEMICN,EOFILE};
#endif