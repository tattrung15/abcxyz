#include<iostream>

using namespace std;

void Swap(int &x, int &y){
	int temp = x;
	x = y;
	y = temp;
}

void BubbleSort(int a[], int n){
	for(int i = 0; i < n - 1; i++){
		for(int j = n - 1; j > i; j--){
			if(a[j - 1] > a[j]){
				Swap(a[j - 1], a[j]);
			}
		}
	}
}

int BinarySearch(int a[], int l, int h, int x){
	while(l <= h){
		int m = l + (h - l)/2;
		if(a[m] == x){
			return m;
		}
		if(a[m] < x){
			l = m + 1;
		}
		if(a[m] > x){
			h = m - 1;
		}
	}
	return -1;
}

int main(){
	int n, x;
	cout << "Nhap so phan tu: ";
	cin >> n;
	int a[n];
	for(int i = 0; i < n; i++){
		cout << "Nhap a[" << i << "] = ";
		cin >> a[i];
	}
	cout << "Mang vua nhap: " << endl;
	for(int i = 0; i < n; i++){
		cout << a[i] << " ";
	}
	BubbleSort(a, n);
	cout << "\nNhap x: ";
	cin >> x;
	int vt = BinarySearch(a, 0, n - 1, x);
	if(vt != -1){
		cout << "Tim thay x, vi tri: " << vt;
	} else {
		cout << "Khong tim thay x";
	}
	return 0;
}
