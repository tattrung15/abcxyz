#include <stdio.h>
#include <conio.h>
#define MAX 100

void nhapmang(float a[MAX][MAX], int n) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			printf("Nhap a[%d][%d] = ", i+1, j+1);
			scanf("%f", &a[i][j]);
		}
	}
}

void inmang(float a[MAX][MAX], int n) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			printf("%7.2f", a[i][j]);
		}
		printf("\n\n");
	}
}

float dinhthuc(float a[MAX][MAX], int n) {
	int s=1;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(i==j) {
				s*=a[i][j];
			}
		}
	}
	return s;
}


int main() {
	int n;
	float a[MAX][MAX];
	float m;
	char chon;
abc:
	printf("Nhap ma tran co NxN: ");
	scanf("%d", &n);
	nhapmang(a,n);
	printf("\nMa tran ban dau:\n\n");
	inmang(a,n);
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			m=-a[j][i]/a[i][i];
			for(int k=i; k<n; k++) {
				a[j][k]+=a[i][k]*m;
			}
		}
	}
	printf("\nMa tran sau khi chuyen thanh ma tran tam giac:\n\n");
	inmang(a,n);
	printf("\nDinh thuc cua ma tran = %.2f\n\n", dinhthuc(a,n));
	printf("Ban co muon tiep tuc khong? (y/n): \n\n");
	chon = getch();
	if(chon != 'y') {
		return 0;
	} else {
		goto abc;
	}
	return 0;
}

