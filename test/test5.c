/*test 5*/
int number[20];
int max(int n)
{
	int i,m;
	m=0;
	i=0;
	do{
      if(number[i]>m)m=number[i];
      i=i+1;
	}while(i<n)
	return m;
}
int sum (int n)
{
	int i,s;
	s=0;
	for(i=0;i<n;i=i+1)
		s=s+number[i];
	return s;
}
float average(int n)
{
	float m;
	m=n;
	return sum(n)/m;
}
float var(int n)
{
	float s,m,ave;
	int i;
	m=n;
	ave=average(n);
	for(i=0;i<n;i=i+1)
		s=s+(number[i]-ave)*(number[i]-ave);
	return s/m;
}
void draw(int n)
{
	int m,i,j;
	char nl;
	nl=10;
	m=max(n);
	for(i=m;i>0;i=i-1)
	{
		for(j=0;j<n;j=j+1)
		{
			if(number[j]>=i)
				printf("*");
			else
				printf(" ");
		}
		printf(nl);
	}
}

void main()
{
	int n,i;
	char nl;
	nl=10;
	printf("please input how many numbers");
	scanf(n);
	printf("please input numbers",nl);
	for(i=0;i<n;i=i+1)
	{
		scanf(number[i]);
	}
	printf("the max number is:",max(n),nl);
	printf("the sum is:",sum(n),nl);
	printf("the average is:",average(n),nl);
	printf("the var is:",var(n),nl);
	draw(n);

}