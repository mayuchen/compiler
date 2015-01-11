void main()
{
	const int i0=10;
	const float f0=3.1415926;
	const char c0='A';
	int i1,i2,i3;
	float f1,f2,f3;
	char c1,c2;
	i1=(-3+10*i0-5)/16;
	i2=c1+10+3.5*2;
	i3=f0*2;
	printf(i0,'\n',i1,'\n',i2,'\n',i3,'\n');/*10 5 17 6*/
	f1=(-3+10*i0-5)/16;
	f2=(-3.0+10*i0-5)/16;
	f3=(i0+2)*f0;
	printf(f0,'\n',f1,'\n',f2,'\n',f3,'\n');/*5.0000 5.7500 37....*/
	c1=33;
	c2=c0+3;
	printf(c1,c2,'\n');/*! D*/
}
 
