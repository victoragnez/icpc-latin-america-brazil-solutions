#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 1;
int k, n, cnt[1001], freq[MAXN];

bool check(){
	for(int i = 1; i <= k; i++)
		if(cnt[i] != cnt[1])
			return 0;
	return 1;
}

int main() {
	scanf("%d%d", &k, &n);
	for(int i = 0; i < n; i++){
		int v;
		scanf("%d", &v);
		cnt[v]++;
	}
	
	for(int i = 1; i <= k; i++){
		cnt[i]++;
		if(check()){
			printf("+%d\n", i);
			return 0;
		}
		cnt[i]--;
	}
	
	for(int i = 1; i <= k; i++){
		cnt[i]--;
		if(check()){
			printf("-%d\n", i);
			return 0;
		}
		cnt[i]++;
	}
	
	for(int i = 1; i <= k; i++)
		freq[cnt[i]]++;
	
	for(int i = 1; i <= k; i++){
		if(freq[cnt[i]] == 1 && freq[cnt[i] + 1] == k-2){
			for(int j = 1; j <= k; j++){
				if(freq[cnt[j]] == 1 && cnt[j] == cnt[i] + 2){
					printf("-%d +%d\n", j, i);
					return 0;
				}
			}
		}
	}
	
	puts("*");
}
