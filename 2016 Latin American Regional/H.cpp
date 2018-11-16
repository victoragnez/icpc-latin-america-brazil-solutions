#include<bits/stdc++.h>
using namespace std;

priority_queue<int, vector<int>, greater<int> > bests;
int n, k, qt, ans;

int main(){
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; i++){
		int v;
		scanf("%d", &v);
		ans += v;
		if((i + 1) % (k + 1) == 0){
			bests.push(v);
		}
		else if(!bests.empty() && bests.top() < v){
			bests.pop();
			bests.push(v);
		}
	}
	while(!bests.empty()){
		ans -= bests.top();
		bests.pop();
	}
	printf("%d\n", ans);
}
