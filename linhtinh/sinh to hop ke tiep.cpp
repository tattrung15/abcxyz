#include<iostream>

using namespace std;

void xuly(int n, int k, int so){
	int a[100], b[100];
	
	int dem = 1;
	while(so != 0){
		int temp = so%10;
		b[dem++] = temp;
		so/=10;
	}
	
	int j = 1;
	for(int i = k; i >= 1; i--){
		a[j++] = b[i];
	}
	
	bool check = false;
	for(int i = k; i >= 1; i--){
		if(a[i] != (n - k + i)){
			check = true;
			a[i]++;
			int l = 1;
			for(int j = i + 1; j <= k; j++){
				a[j] = a[i] + l;
				l++;
			}
			break;
		}
	}
	
	if(check){
		cout << "So to hop ke tiep la: " << endl;
		for(int i = 1 ; i <= k; i++){
			cout << a[i];
		}
	} else {
		cout << "Day la to hop cuoi cung.";
	}
}

int main(){
	int n, k, so;
	cout << "Nhap n >= k: ";
	cin >> n >> k;
	cout << "Nhap so to hop hien tai: ";
	cin >> so;
	xuly(n, k, so);
}
