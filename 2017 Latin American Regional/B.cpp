#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 1;
char s[MAXN];
bool vowel[256];
int n, ans, ac[MAXN];

void solve(int l, int r, int t){
	if(r-l+1 == 1){
		ans++;
		return;
	}
	
	int a, b;
	if(!t){
		a = vowel[(int)s[l]];
		b = vowel[(int)s[r]];
	}
	else{
		a = vowel[(int)s[r]];
		b = vowel[(int)s[l]];
	}
	
	if(a==0 && b==1)
		return;
		
	if(a==1 && b==1){
		if(!t)
			solve(l+1,r,1);
		else
			solve(l,r-1,0);
	}
	else if(a==0 && b==0){
		if(!t)
			solve(l,r-1,0);
		else
			solve(l+1,r,1);
	}
	else{
		int q = ac[r];
	
		if(l != 0)
			q -= ac[l-1];
	
		if(q == 1)
			ans++;
			
		if(!t)
			solve(l,r-1,0);
		else
			solve(l+1,r,1);
	}
}

int main(){
	vowel[(int)'a'] = vowel[(int)'e'] = vowel[(int)'i'] = vowel[(int)'o'] = vowel[(int)'u'] = true;
	
	scanf("%s", s);
	n = (int)strlen(s);
	
	for(int i = 0; i < n; i++){
		ac[i] = vowel[(int)s[i]];
		if(i > 0)
			ac[i] += ac[i-1];
	}
	
	solve(0, n-1, 0);
	printf("%d\n", ans);
}
