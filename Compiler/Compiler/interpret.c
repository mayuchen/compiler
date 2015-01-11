#define STACKSIZE 500
#define GSTACKSIZE 50
#include "pcodename.h"
#include<stdio.h>
#include"systemconfig.h"///
int init();
int fill(int ptr,int type,int v);
int fillf(int ptr,int type,float v);
extern struct PCODE Pcodes[];
//struct stackitem stack[STACKSIZE];//运行栈
DATA stack[STACKSIZE];
DATA gstack[GSTACKSIZE];
DATA register_rts[1];
char string[STRINGNUM][TOKENLENGTH];
int stringptr=0;
int gt=1;
int base (int l,int b);
int interpret()//pcode解释执行器
{
	int p,b,t;//program-register,base-register,topstack-register 
//	int l;
	struct PCODE i; //struction register

    t = -1;
    b = 0;
    p = 0;
	init();
    do{
		i = Pcodes[p];
		p = p+1;
      //with i do
		switch (i.codename)
		{
		case NOP:
			break;
		case LIT : 
            t = t+1;
		    fill(t,I,i.i);
			//stack[t].i = i.a;
			break;
		case LITC:
            t = t+1;
			fill(t,C,i.i);
			//stack[t].i = i.a;
			break;
		case LITF:
			t=t+1;
			fillf(t,F,i.f);
			break;
		case OPR :
			switch (i.i)
			{
			case RET: //return
				t = b-1;
				p = stack[t+2].i;
				b = stack[t+1].i;
				break;
			case RTS://return sto
				{
					int tx=t;
					t=b-1;
					p = stack[t+2].i;
					b = stack[t+1].i;
					//register_rts[0].type=stack[tx].type;//
					register_rts[0].type=i.l;
					register_rts[0].i=stack[tx].i;
					register_rts[0].f=stack[tx].f;
				}
				break;
			case LRS:
				t++;
				stack[t].type=register_rts[0].type;
				stack[t].i=register_rts[0].i;
				stack[t].f=register_rts[0].f;
				break;
			case OPP://opppsite number
		
					stack[t].f=-stack[t].f;
			
					stack[t].i=-stack[t].i;
				break;		
			case ADD:
				t = t-1;
				if(stack[t].type!=F&&stack[t+1].type!=F)
					{
						stack[t].type=I;
						stack[t].i=stack[t].i+stack[t+1].i;
						stack[t].f=(float)stack[t].i;
					}
				else
				{
					stack[t].type=F;
					stack[t].f=stack[t].f+stack[t+1].f;
					stack[t].i=(int)stack[t].f;
				}
				break;
			case MNS:
				t = t-1;
				if(stack[t].type!=F&&stack[t+1].type!=F)
					{
						stack[t].type=I;
						stack[t].i=stack[t].i-stack[t+1].i;
						stack[t].f=(float)stack[t].i;
					}
				else
				{
					stack[t].type=F;
					stack[t].f=stack[t].f-stack[t+1].f;
					stack[t].i=(int)stack[t].f;
				}
				break;
			case MUL:
				t = t-1;
				if(stack[t].type!=F&&stack[t+1].type!=F)
					{
						stack[t].i=stack[t].i*stack[t+1].i;
						stack[t].f=(float)stack[t].i;
					}
				else
				{
					stack[t].type=F;
					stack[t].f=stack[t].f*stack[t+1].f;
					stack[t].i=(int)stack[t].f;
				}
				break;
			case DIVI:
				t = t-1;
				if(stack[t].type!=F&&stack[t+1].type!=F)
					{
						stack[t].type=I;
						stack[t].i=stack[t].i/stack[t+1].i;
						stack[t].f=(float)stack[t].i;
					}
				else
				{
					stack[t].type=F;
					stack[t].f=stack[t].f/stack[t+1].f;
					stack[t].i=(int)stack[t].f;
				}
				break;
			case PEQU:
				t=t-1;
				if(stack[t].type!=F&&stack[t+1].type!=F)
					{
						stack[t].type=I;
						stack[t].i=(stack[t].i==stack[t+1].i?1:0);
					}
				else
				{
					stack[t].type=I;
					stack[t].i=(stack[t].f==stack[t+1].f?1:0);
				}

				break;
			case PNEQ:
				t=t-1;
				if(stack[t].type!=F&&stack[t+1].type!=F)
					{
						stack[t].type=I;
						stack[t].i=(stack[t].i!=stack[t+1].i?1:0);
					}
				else
				{
					stack[t].type=I;
					stack[t].i=(stack[t].f!=stack[t+1].f?1:0);
				}
				break;
			case BIG:
				t=t-1;
				if(stack[t].type!=F&&stack[t+1].type!=F)
					{
						stack[t].type=I;
						stack[t].i=(stack[t].i>stack[t+1].i?1:0);
					}
				else
				{
					stack[t].type=I;
					stack[t].i=(stack[t].f>stack[t+1].f?1:0);
				}
				break;
			case BEQ:
				t=t-1;
				if(stack[t].type!=F&&stack[t+1].type!=F)
					{
						stack[t].type=I;
						stack[t].i=(stack[t].i>=stack[t+1].i?1:0);
					}
				else
				{
					stack[t].type=I;
					stack[t].i=(stack[t].f>=stack[t+1].f?1:0);
				}
				break;
			case SMA:
				t=t-1;
				if(stack[t].type!=F&&stack[t+1].type!=F)
					{
						stack[t].type=I;
						stack[t].i=(stack[t].i<stack[t+1].i?1:0);
					}
				else
				{
					stack[t].type=I;
					stack[t].i=(stack[t].f<stack[t+1].f?1:0);
				}
				break;
			case SEQ:
				t=t-1;
				if(stack[t].type!=F&&stack[t+1].type!=F)
					{
						stack[t].type=I;
						stack[t].i=(stack[t].i<=stack[t+1].i?1:0);
					}
				else
				{
					stack[t].type=I;
					stack[t].i=(stack[t].f<=stack[t+1].f?1:0);
				}
				break;
			case NON:
				if(stack[t].type!=F)
					stack[t].i=(stack[t].i==0?1:0);
				else
					stack[t].i=(stack[t].f==0?1:0);
				stack[t].type=I;
				break;
			default:
				break;
			}
			break;
		case LOD:
			if (i.l==0)///LOD段内栈顶
			{
				
				int tmp=stack[t].i;
				stack[t].type=stack[b+tmp].type;
				stack[t].i=stack[b+tmp].i;
				stack[t].f=stack[b+tmp].f;
			}
			else if(i.l==1)//LOD段内立即数
			{
				t = t+1;
				stack[t].type = stack[b+i.i].type;
				stack[t].i = stack[b+i.i].i;
				stack[t].f = stack[b+i.i].f;
			}
			else if(i.l==2)//LOD全局栈顶
			{
				int tmp=stack[t].i;
				stack[t].type=gstack[tmp].type;
				stack[t].i=gstack[tmp].i;
				stack[t].f=gstack[tmp].f;
			}
			else if(i.l==3)//LOD全局立即数
			{
				t = t+1;
				stack[t].type = gstack[i.i].type;
				stack[t].i = gstack[i.i].i;
				stack[t].f = gstack[i.i].f;
			}
			break;
		case STO :///改完没测试 
			if(i.l==0)///将栈顶元素存到次栈顶地址(段内偏移)
			{
				//stack[b+stack[t-1].i].type = stack[t].type;  //{ writeln(s[t]); }
			//	stack[b+stack[t-1].i].type = stack[t].type;
				if(stack[b+stack[t-1].i].type==F)
				{
				stack[b+stack[t-1].i].f = stack[t].f;
				stack[b+stack[t-1].i].i = (int)stack[t].f;
				}
				else
				{
					stack[b+stack[t-1].i].i = stack[t].i;
					stack[b+stack[t-1].i].f = stack[t].i;
				}
				t = t-2;
			}
			else if(i.l==1)///将栈顶元素存到立即数地址（段内偏移）
			{
				//stack[b+i.i].type = stack[t].type;  //{ writeln(s[t]); }
				//stack[b+i.i].type = stack[t].type;
				if(stack[b+i.i].type==F)
				{
					stack[b+i.i].f = stack[t].f;
					stack[b+i.i].i = (int)stack[t].f;
				}
				else
				{
					stack[b+i.i].i=stack[t].i;
					stack[b+i.i].f=stack[t].i;
				}
				t = t-1;
			}
			else if(i.l==2)//将栈顶元素存到次栈顶绝对地址
			{
				//stack[stack[t-1].i].type = stack[t].type;  //{ writeln(s[t]); }
				//stack[stack[t-1].i].type = stack[t].type;
				if(gstack[stack[t-1].i].type==F)
				{
				gstack[stack[t-1].i].f = stack[t].f;
				gstack[stack[t-1].i].i = (int)stack[t].f;
				}
				else
				{
					gstack[stack[t-1].i].i = stack[t].i;
					gstack[stack[t-1].i].f = stack[t].i;
				}
				t = t-2;
			}
			else if(i.l==3)//将栈顶元素存到立即数绝对地址
			{
				//stack[i.i].type = stack[t].type;  //{ writeln(s[t]); }
				//stack[i.i].type=stack[i.i].type;
				if(gstack[i.i].type==F)
				{
					gstack[i.i].f = stack[t].f;
					gstack[i.i].i = (int)stack[t].f;
				}
				else
				{
					gstack[i.i].i=stack[t].i;
					gstack[i.i].f=stack[t].i;
				}
				t = t-1;
			}
            break;
		case CAL:	//{ generate new block mark }
			//stack[t+1].i = base(i.l,b);//当前函数基地址
			stack[t+1].i = b;//调用cal的函数的地址
			stack[t+2].i = p;//program-register
			
			////t = t+3;//?????
            b = t+1;
			p = i.i;
			t=  t+2;
            break;
		case INT:
			{
				int tmp=t;
				t = t+i.i;
				for(tmp++;tmp<=t;tmp++)
					stack[tmp].type=i.l;
			}
			break;
		case GINT:
			{
				int tmp=gt;
				gt=gt+i.i;
				for(tmp++;tmp<=gt;tmp++)
					gstack[tmp].type=i.l;
			}
			break;
		case JMP:
			p=i.i;
			break;
		case JPC:
			if(stack[t].i==0)
			{
				p=i.i;
				t=t-1;
			}
			else
				t--;
			break;
		case REDI:
			//printf("Pcode:RED input a integer.\n");
			t++;
			stack[t].type=I;
			scanf_s("%d",&stack[t].i);
			stack[t].f=(float)stack[t].i;
			break;
		case REDC:
			//printf("Pcode:RED input a character.\n");
			t++;
			stack[t].type=C;
			scanf_s("%c",&stack[t].i);
			stack[t].f=(float)stack[t].i;
			break;
		case REDF:
			//printf("Pcode:RED input a float.\n");
			t++;
			stack[t].type=F;
			scanf_s("%f",&stack[t].f);
			stack[t].i=(int)stack[t].f;
			break;
		case WRT:
			if(stack[t].type==I)
				printf("%d",stack[t].i);
			else if(stack[t].type==F)
				printf("%f",stack[t].f);
			else if(stack[t].type==C)
				printf("%c",stack[t].i);
			else
				printf("%d",stack[t].i);
			t--;
			break;
		case WRTS:
			printf("%s",string[i.i]);
			break;
		default:
			return -1;
		}
		if (t>=STACKSIZE)
		return -2;
	}while (p!=0);//主函数返回？
	return 0;
}
int base (int l,int b)
{
	int b1=b;
	while(l>0)
	{
		b1=stack[b1].i;
		l--;
	}
	return b1;
}
int init()
{
	int i;
	for(i=0;i<3;i++)
	{
		stack[i].type=0;
		stack[i].f=0;
		stack[i].i=0;
	}
	return 0;
}
int fill(int ptr,int type,int v)
{
	stack[ptr].type=type;
	stack[ptr].i=v;
	stack[ptr].f=(float)v;
	return 0;
}
int fillf(int ptr,int type,float v)
{
	stack[ptr].type=type;
	stack[ptr].i=(int)v;
	stack[ptr].f=v;
	return 0;
}
/*  function base( l : integer ): integer;
    var b1 : integer;
    begin { find base l levels down }
      b1 := b;
      while l > 0 do
        begin
          b1 := s[b1];
          l := l-1
        end;
      base := b1
    end; { base }*/