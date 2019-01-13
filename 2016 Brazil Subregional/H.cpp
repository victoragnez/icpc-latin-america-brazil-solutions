#include<bits/stdc++.h>
using namespace std;

char s[50];

int main(){
	int n = 0;
	while(scanf(" %c", s + n) != EOF){
		if(s[n] == 'a' || s[n] == 'e' || s[n] == 'i' || s[n] == 'o' || s[n] == 'u')
			n++;
	}
	for(int i = 0; i < n / 2; i++){
		if(s[i] != s[n - 1 - i]){
			puts("N");
			return 0;
		}
	}
	puts("S");
}

