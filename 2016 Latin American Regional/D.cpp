#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 1;

int n, vet[MAXN];
deque<int> order;

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", vet+i);
	sort(vet, vet+n);
	reverse(vet, vet+n);
	for(int i = 0;  i < n; i++){
		if(i & 1)
			order.push_back(vet[i]);
		else
			order.push_front(vet[i]);
	}
	double ans = 0, last_x = -1, last_y = -1;
	for(int i = 0; i <= n; i++){
		double ang = (i % n) * (2 * M_PI / n);
		double cur_x = cos(ang) * order[i % n];
		double cur_y = sin(ang) * order[i % n];
		
		if(i > 0)
			ans += last_x * cur_y - last_y * cur_x;
		
		last_x = cur_x;
		last_y = cur_y;
	}
	
	printf("%.3f\n", ans * 0.5);
}
