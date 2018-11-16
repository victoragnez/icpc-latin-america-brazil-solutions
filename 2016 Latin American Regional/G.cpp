#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 1;
char s[MAXN];
int n, m, tex[MAXN], vet[MAXN], F[MAXN], last[26], ans;

int main(){
	scanf("%s", s);
	n = (int)strlen(s);
	scanf("%d", &m);
	for(int i = 0; i < m; i++){
		scanf("%d", &vet[i]);
		vet[i]--;
	}

	memset(last, -1, sizeof(last));
	for(int i = 0; i < n; i++){
		int v = s[i] - 'a';
		if(last[v] == -1)
			tex[i] = -1;
		else
			tex[i] = i - last[v];
		last[v] = i;
	}

	memset(last, -1, sizeof(last));
	for(int i = 0; i < m; i++){
		int v = vet[i];
		if(last[v] == -1)
			vet[i] = -1;
		else
			vet[i] = i - last[v];
		last[v] = i;
	}

	// KMP
	int i = 0, j = F[0] = -1;
	while(i < m){
		while(j >= 0 && (vet[i] > j ? -1 : vet[i]) != vet[j])
			j = F[j];
		F[++i] = ++j;
	}
	i = j = 0;
	while(i < n){
		while(j >= 0 && (tex[i] > j ? -1:  tex[i]) != vet[j])
			j = F[j];
		if(++j == m){
			ans++;
			j = F[j];
		}
		i++;
	}

	printf("%d\n", ans);
}

