#include <stdio.h>
#include <conio.h>
#define MAX 100

void nhapmang(float a[MAX][MAX], int m, int n)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("Nhap a[%d][%d] = ", i+1, j+1);
			scanf("%f", &a[i][j]);
		}
	}
}

void inmang(float a[MAX][MAX], int m, int n)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("%7.2f", a[i][j]);
		}
		printf("\n\n");
	}
}


int main()
{
	int m, n;
	float a[MAX][MAX];
	float q;
	char chon;
	abc:
	printf("Nhap m: ");
	scanf("%d", &m);
	printf("Nhap n: ");
	scanf("%d", &n);
	nhapmang(a,m,n);
	printf("\nMa tran ban dau:\n\n");
	inmang(a,m,n);
	for(int i=0; i<m; i++)
	{
		for(int j=i+1; j<m; j++)
		{
			q=-a[j][i]/a[i][i];
			for(int k=i; k<n; k++)
			{
				a[j][k]+=a[i][k]*q;
			}
		}
	}
	printf("\nMa tran sau khi chuyen thanh ma tran tam giac:\n\n");
	inmang(a,m,n);
	//code
	//printf("\nHang (rank) cua ma tran la:\n\n");
	printf("Ban co muon tiep tuc khong? (y/n): \n\n");
	chon = getch();
	if(chon != 'y')
	{
		return 0;
	}
	else
	{
		goto abc;
	}
	return 0;
}

