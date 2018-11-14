#include <bits/stdc++.h>
using namespace std;

struct SuffixArray{
	int n, h;
	vector<int> sa, invsa;
	
	SuffixArray(){}
	SuffixArray(vector<int> v) : n((int)v.size()), sa(n){
		init(v);
	}
	
	bool cmp(int a, int b){
		return invsa[a + h] < invsa[b + h];
	}
	
	void ternary_sort(int a, int b){
		if(a == b)
			return;
		
		int pivot = sa[a + rand() % (b - a)];
		int left = a, right = b;
		
		for(int i = a; i < b; i++)
			if(cmp(sa[i], pivot))
				swap(sa[i], sa[left++]);
		for(int i = b-1; i >= left; i--)
			if(cmp(pivot, sa[i]))
				swap(sa[i], sa[--right]);
		
		ternary_sort(a, left);
		for(int i = left; i < right; i++)
			invsa[sa[i]] = right - 1;
		if(right-left == 1)
			sa[left] = -1;
		ternary_sort(right, b);
	}
	
	void init(vector<int> & v){
		v.push_back(INT_MIN);
		for(int i = 0; i < n; i++)
			sa[i] = i;
		
		invsa = v;
		h = 0;
		ternary_sort(0, n);
		
		for(h = 1; h <= n; h *= 2){
			for(int j = 0, i = j; i != n; i = j){
				if(sa[i] < 0){
					while(j < n && sa[j] < 0)
						j += -sa[j];
					sa[i] = -(j-i);
				}
				else{
					j = invsa[sa[i]]+1;
					ternary_sort(i, j);
				}
			}
		}
		
		for(int i = 0; i < n; i++)
			sa[invsa[i]] = i;
	}
	
	int operator[](int id){
		return sa[id];
	}
	
	int inv(int p){
		return invsa[p];
	}
};

int n;
vector<int> vet, pos, res;
long long ans, val = 1, mod = 1e9+7;

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		pos.emplace_back((int)vet.size());
		int k;
		scanf("%d", &k);
		for(int j = 0; j < k; j++){
			int v;
			scanf("%d", &v);
			vet.emplace_back(v);
		}
		vet.emplace_back(301);
	}
	
	SuffixArray suf(vet);
	set<int> best;
	
	for(int i = 0; i < (int)pos.size(); i++)
		best.insert(suf.inv(pos[i]));
	
	for(int i = 0; i < (int)vet.size() - n; i++){
		int p = suf[*best.begin()];
		best.erase(best.begin());
		best.insert(suf.inv(p + 1));
		res.emplace_back(vet[p]);
	}
	
	for(int i = (int)res.size()-1; i >= 0; i--){
		val = val * 365 % mod;
		ans = (ans + val * res[i]) % mod;
	}
	
	printf("%lld\n", ans);
}

