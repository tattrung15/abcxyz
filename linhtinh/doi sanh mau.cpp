#include <iostream>
#include <string.h>
 
using namespace std;

int BruteForce(char str1[], char str2[], int len1, int len2){
	int count = 0;
	for(int i = 0; i <= len1 - len2; i++){
		for(int j = 0; j < len2 && str2[j] == str1[i + j]; j++){
			if(j >= len2 - 1){
				count++;
			}
		}
	}
	return count;
}

int main() {
	char str1[50];
	char str2[50];
	gets(str1);
	gets(str2);
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int res = BruteForce(str1, str2, len1, len2);
	cout << res;
}
