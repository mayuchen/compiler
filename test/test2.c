const char c='!';
int i[10],ii;
int iii;
int fun(int a,int b)
{
    int s;
    i[a]=b;
    return a+b;
}
void main()
{
	ii=fun(1,2);
	fun(2,6);
	printf("this is a string",ii,i[1],i[2],c);/*this is a string 326!*/
}
 
