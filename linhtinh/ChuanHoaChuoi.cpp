#include<iostream>
#include<string.h>

using namespace std;

int main(){
	char a[] = "   bui    tat    trung   ";
	
	while(a[0] == ' '){
		strcpy(&a[0], &a[1]);
	}
	
	a[0] = toupper(a[0]);
	
	for(int i = 0; i < strlen(a) - 1; i++){
		if(a[i] == ' ' && a[i + 1] == ' '){
			strcpy(&a[i], &a[i + 1]);
			i--;
		}
	}
	
	while(a[strlen(a) - 1] == ' '){
		strcpy(&a[strlen(a) - 1], &a[strlen(a)]);
	}
	
	cout << a << "|";
	return 0;
}
