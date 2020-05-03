#include <stdio.h>
#define MAX 100

void nhapmang(int a[MAX][MAX], int m, int n)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("Nhap a[%d][%d] = ", i+1, j+1);
			scanf("%d", &a[i][j]);
		}
	}
}

void inmang(int a[MAX][MAX], int m, int n)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("%4d", a[i][j]);
		}
		printf("\n");
	}
}

int tonghangi(int a[MAX][MAX], int i, int n)
{
	int s=0;
	for(int j=0;j<n;j++)
	{
		s += a[i][j];
	}
	return s;
}

int timmax(int a[MAX][MAX], int m, int n)
{
	int h=1;
	int max = tonghangi(a,0,n);
	for(int i=0;i<m;i++)
	{
		if(tonghangi(a,i,n) > max)
		{
			max = tonghangi(a,i,n);
			h++;
		}
	}
	return h;
}

int main()
{
	int m, n;
	int a[MAX][MAX];
	printf("Nhap m: ");
	scanf("%d", &m);
	printf("Nhap n: ");
	scanf("%d", &n);
	nhapmang(a,m,n);
	inmang(a,m,n);
	printf("\n%d", timmax(a,m,n));
	return 0;
}

