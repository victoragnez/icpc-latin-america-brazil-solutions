#include<bits/stdc++.h>
using namespace std;

int main(){
	int ans = 0;
	char c;
	while(scanf(" %c", &c) != EOF)
		ans += c - '0';
	printf("%d\n", ans % 3);
}
