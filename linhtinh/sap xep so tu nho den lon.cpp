#include <stdio.h>
#include <stdlib.h>

int compare(const void* stt1, const void* stt2)
{
	return (*(int *)stt1 - *(int *)stt2);
}


int main ()
{
	
	int n, width, num, i;
	printf("Nhap so phan tu cua mang: ");
	scanf("%d", &n);
	int x[n];
	for (i = 0; i < n; i++) 
	{
    printf("Nhap x[%d] = ", i);
    scanf("%d", &x[i]);
	}
	printf("Day so vua nhap la: ");
	for (int j=0;j<n;j++)
	{
		printf("%d  ", x[j]);
	}
	num = sizeof(x)/sizeof(x[0]);
	width = sizeof(x[0]);
	qsort(x, num, width, compare);
	printf("\nDay so sau khi sap xep la: ");
	for (int j=0;j<n;j++)
	{
		printf("%d  ", x[j]);
	}
	return 0;
}
