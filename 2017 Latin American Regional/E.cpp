#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000 + 1;

char s[MAXN], dp[MAXN][MAXN], opt[MAXN][MAXN];
int n, k;

char solve(int i, int r){
	if(i == n)
		return !r;
	char & ret = dp[i][r];
	if(ret != 2)
		return ret;
	ret = 0;
	if(s[i] != '?'){
		char d = char(s[i] - '0');
		if(solve(i + 1, (10 * r + d) % k)){
			opt[i][r] = d;
			ret = 1;
		}
	}
	else{
		for(char d = !i; d < 10; d++){
			if(solve(i + 1, (10 * r + d) % k)){
				opt[i][r] = d;
				ret = 1;
				break;
			}
		}
	}
	return ret;
}

void recover(int i, int r){
	if(i == n){
		printf("\n");
		return;
	}
	printf("%c", char('0' + opt[i][r]));
	recover(i + 1, (10 * r + opt[i][r]) % k);
}

int main() {
	memset(dp, (char)2, sizeof(dp));
	memset(opt, (char)11, sizeof(opt));
	scanf("%s%d", s, &k);
	n = (int)strlen(s);
	if(!solve(0, 0)){
		puts("*");
		return 0;
	}
	recover(0, 0);
}

