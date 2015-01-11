#include<stdio.h>
#include"error.h"
extern FILE* err;
extern int linenum;
int errnum=0;
int error(int errortype)
{
	errnum++;
	fprintf(err,"Error %d:C%d ",errnum,errortype);
	switch (errortype)
	{
	case UNKNOWN_SYMBOL:
		fprintf(err,"unknown symbol in line");break;
	case STRING_TOO_LONG:
		fprintf(err,"string is too long");break;
	case WRONG_FORMAT_REAL_NUMBER:
		fprintf(err,"wrong format real number");break;
	case WRONG_FORMAT_INTEGER:
		fprintf(err,"wrong format integer");break;
	case UNFINISHED_STRING:
		fprintf(err,"\'\"\'dismatch");break;
	case UNFINISHED_PROGRAM:
		fprintf(err,"the program is not finished");break;
	case MISSING_SEMICN:
		fprintf(err,"sentence misses semicn");break;
	case DECLARATION_IS_NOT_START_WITH_TYPE:
		fprintf(err,"declartion is not start with type");break;
	case DECLARATION_HAVE_NO_EQL:
		fprintf(err,"wrong format of constant declartion");break;
	case DECLARATION_SHOULD_HAVE_A_ID:
		fprintf(err,"declartion should have a id");break;
	case WRONG_ASSIGN_SYNTAX:
		fprintf(err,"should not use assign symbol");break;
	case WRONG_EXPRESSION:
		fprintf(err,"wrong expression");break;
	case ARRAY_OVERFLOW:
		fprintf(err,"array overflow");break;
	case ARRAY_SUBVALUE_SHOULD_BE_INTEGER:
		fprintf(err,"array subvalue should be an integer");break;
	case USING_AN_ICON_WITHOUT_DECLARTION:
		fprintf(err,"non-declartion variable");break;
	case ERROR_VARIABLEDELARTION:
		fprintf(err,"error variable decleartion");break;
	case ERROR_DATA_TYPE:
		fprintf(err,"error data type");break;
	case ERROR_FUNCTIONDELARATION:
		fprintf(err,"error function declartion");break;
	case RE_DECLARATION:
		fprintf(err,"re-declartion");break;
	case ERROR_SENTENCE:
		fprintf(err,"error format sentence");break;
	case ERROR_RETURN_TYPE:
		fprintf(err,"error return type");break;
	case PARENT_DISMATCH:
		fprintf(err,"parent dismatch");break;
	case ERROR_FOR_SENTENCE:
		fprintf(err,"for sentence error");break;
	case ERROR_PROGRAM_STRUCTURE:
		fprintf(err,"error program structure");break;
	case ERROR_IN_WRITE_SENTENCE:
		fprintf(err,"error in write sentence");break;
	case ERROR_IN_READ_SENTENCE:
		fprintf(err,"error int read sentence");break;
	case MISSING_WHILE:
		fprintf(err,"miss while condition");break;
	case MISSING_SENTENCE:
		fprintf(err,"miss sentence");break;
	}
	fprintf(err," in line %d\n",linenum+1);
	return errortype;
};