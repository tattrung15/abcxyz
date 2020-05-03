#include<iostream>
#include<string>
#include<stack>

using namespace std;

int Priority(char a){
	if(a == '(') return 0;
	if(a == '+' || a == '-') return 1;
	if(a == '*' || a == '/' || a == '%') return 2;
	if(a == '^') return 3;
}

void Convert(string input){
	stack<char> s;
	int i = 0;
	string strTemp = "";
	while(i < input.length()){
		char c = input.at(i);
		if(c != ' '){
			if(c - '0' <= 9 && c - '0' >= 0 || isalpha(c)) strTemp += c;
			else {
				cout << strTemp << " ";
				strTemp = "";
				if(c == '(') s.push(c);
				else {
					if(c == ')'){
						while(s.top() != '('){
							cout << s.top();
							s.pop();
						}
						s.pop();
					} else {
						while(!s.empty() && Priority(c) <= Priority(s.top())){
							cout << s.top();
							s.pop();
						}
						s.push(c);
					}
				}
			}
		}
		i++;
	}
	if(strTemp != "") cout << strTemp << " ";
	while(!s.empty()){
		cout << s.top();
		s.pop();
	}
}

int main(){
	freopen("INPUT.TXT", "r", stdin);
	freopen("OUTPUT.TXT", "a+", stdout);
	string input;
	getline(cin, input);
	Convert(input);
	return 0;
}
