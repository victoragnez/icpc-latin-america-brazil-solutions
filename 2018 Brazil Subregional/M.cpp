#include <bits/stdc++.h>
using namespace std;
const int MAXN =  2000 + 1;

bitset<MAXN> mod_gauss(vector<bitset<MAXN> > &U, bitset<MAXN> b){
	int n = (int)U.size();
	int l = 0;
	vector<int> row(n,-1);
	for(int c = 0; c < n; c++){
		int r = l;
		if(U[l][c] == 0){
			for(int i = l+1; i < n; i++){
				if(U[i][c]){
					r = i;
					break;
				}
			}
		}
		
		if(l!=r){
			swap(U[l], U[r]);
			int t = b[l];
			b[l] = b[r];
			b[r] = t;
		}
		
		if(!U[l][c])
			continue;
		
		row[c] = l;
		for(int i = l+1; i < n; i++){
			if(U[i][c]){
				U[i] ^= U[l];
				b[i] = b[i] ^ b[l];
			}
		}
		l++;
	}
	
	for(int i = 0; i < n; i++){
		if(U[i].count() == 0 && b[i]){
			puts("impossible");
			exit(0);
		}
	}
	
	bitset<MAXN> x;
	for(int i = n-1; i >= 0; i--){
		if(row[i] == -1)
			x[i] = 1;
		else
			x[i] = b[row[i]];
		if(x[i])
			for(int j = 0; j < i; j++)
				if(U[j][i])
					b[j] = b[j]^1;
	}
	return x;
}

int n, m;
vector<bitset<MAXN> > mat;
bitset<MAXN> x;

int main(){
	scanf("%d%d", &m, &n);
	mat.resize(max(m,n));
	for(int i = 0; i < m; i++){
		scanf(" %*c");
		bool v = 1;
		while(1){
			char c;
			scanf(" %c", &c);
			if(c == 'n'){
				scanf("%*c %*c %*c");
				v ^= 1;
			}
			
			int d;
			scanf("%d", &d);
			d--;
			
			mat[i][n-1-d] = mat[i][n-1-d] ^ 1;
			
			scanf(" %c", &c);
			if(c == 'o')
				scanf("%*c");
			else
				break;
		}
		if(i+1 < m)
			scanf(" %*c %*c %*c ");
		if(v)
			x.set(i);
	}
	
	x = mod_gauss(mat, x);
	
	for(int i = 0; i < n; i++){
		if(x[n-1-i])
			printf("T");
		else
			printf("F");
	}
	
	printf("\n");
}

