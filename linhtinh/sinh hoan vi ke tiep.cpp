#include<iostream>

using namespace std;

void hoanvi(int &x, int &y){
	int z = x;
	x = y;
	y = z;
}

void xuly(int n){
	int a[100], b[100];
	int dem = 0;
	while(n != 0){
		int temp = n%10;
		b[dem++] = temp;
		n/=10;
	}
	
	int j = 0;
	for(int i = dem - 1; i >= 0; i--){
		a[j++] = b[i];
	}
	
	bool check = false;
	
	for(int i = dem - 2; i >= 0; i--){
		
		if(a[i] < a[i + 1]){
			check = true;
			int min = i + 1;
			for(int k = i + 2; k < dem; k++){
				if(a[k] < a[min] && a[k] > a[i]){
					min = k;
				}
			}
			
			hoanvi(a[i], a[min]);
			
			for(int j = i + 1; j < dem; j++){
				for(int l = dem - 1; l > j; l--){
					if(a[l - 1] > a[l]){
						hoanvi(a[l - 1], a[l]);
					}
				}
			}
			break;
		}
	}
	
	if(check){
		cout << "So hoan vi ke tiep la: " << endl;
		for(int i = 0 ; i < dem; i++){
			cout << a[i];
		}
	} else {
		cout << "Day la hoan vi cuoi cung.";
	}
	
	
}

int main(){
	int n;
	cout << "Nhap so hoan vi hien tai: ";
	cin >> n;
	xuly(n);
}
