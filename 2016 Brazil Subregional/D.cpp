#include<bits/stdc++.h>
using namespace std;

int a, b, c, d;

bool verify(int n){
	return (n % a == 0) && (n % b != 0) && (c % n == 0) && (d % n != 0);
}

int main(){
	scanf("%d%d%d%d", &a, &b, &c, &d);
	stack<int> divi;
	for(int i = 1; i * i <= c; i++){
		if(c % i == 0){
			if(verify(i)){
				printf("%d\n", i);
				return 0;
			}
			divi.push(c / i);
		}
	}
	while(!divi.empty()){
		int i = divi.top();
		divi.pop();
		if(verify(i)){
			printf("%d\n", i);
			return 0;
		}
	}
	puts("-1");
}

