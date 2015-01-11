#ifndef _SYMNAME_H
#define _SYMNAME_H

enum symbol{
	EOFILE=-1,//�������
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
	NOTESSYM,//ע��
	INTTK,//int
	FLOATTK,//float
	CHARTK,//char
	VOIDTK,
	IDEN,//���Ǳ����ִ���
	INTCON,//����
	FLOATCON,//������
	CHARCON,
	STRCON,
	SPACE ,//�ո�س��Ʊ� 36
	PLUS ,//�ӷ������ 
	MINUS ,//���������
	MULT ,//�Ǻ�
	DIV ,//����
	LPARENT ,//������
	RPARENT ,//������
	LBRACE ,//������
	RBRACE ,//�һ�����
	LBRACK,
	RBRACK,//������ 46
	COMMA ,//����
	SEMICN ,//�ֺ�
	COLON ,//ð��
	ASSIGN ,//��ֵ����
	EQL ,//���ж�
	GRE ,//���ں� 52
	GEQ,//���ڵ���
	LSS,//С�ں�
	LEQ,//С�ڵ���
	NEQ,//�����ں�
	PERIOD,//��
	QMARK,
	DQMARK,//59
	
	EOLINE//һ�д������
};
enum charsymbol{
	DOTC=1,//��
	SINQUOC,//������
	DBLQUOC,//˫����
	SPACEC,//�ո�
	TABC,//�Ʊ�
	NEWLINEC,//�س�
	DIGITC,//����
	LETTERC,//��ĸ
	COLONC,//ð��
	EQUC,//�Ⱥ�
	PLUSC,//�Ӻ�
	MINUSC,//����
	EXCLAMC,//̾��
	STARC,//�Ǻ�
	LPARC,//��С����
	RPARC,//��С����
	COMMAC,//����
	SEMIC,//�ֺ�
	DIVIC,//б��
	LBRACEC,//������
	RBRACEC,//�һ�����
	LABRAC,//�������
	RABRAC,//�Ҽ�����
	LBRACKC,
	RBRACKC,
	ENDLC// \0
};
//int declarfsym[]={CHARTK,FLOATTK,INTTK};
//int sentencend[]={SEMICN,EOFILE};
#endif