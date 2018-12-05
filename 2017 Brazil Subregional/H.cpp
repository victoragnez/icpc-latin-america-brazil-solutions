#include<bits/stdc++.h>
using namespace std;

struct point{
	int x, y;
	point() : x(0), y(0) { }
	point(int X, int Y) : x(X), y(Y) { }
	point operator-(point p){
		return point(x - p.x, y - p.y);
	}
	bool operator<(const point p) const {
		return y < p.y;
	}
};

int cross(point a, point b){
	return a.x * b.y - a.y * b.x;
}

point vet[100];
int dp[100], ans;

int main(){
	int n, xa, xb;
	scanf("%d%d%d", &n, &xa, &xb);
	point a(xa, 0), b(xb, 0);
	for(int i = 0; i < n; i++)
		scanf("%d%d", &vet[i].x, &vet[i].y);
	sort(vet, vet + n);
	for(int i = 0; i < n; i++){
		dp[i] = 1;
		for(int j = 0; j < i; j++)
			if(cross(vet[j] - a, vet[i] - a) > 0 && cross(vet[i] - b, vet[j] - b) > 0)
				dp[i] = max(dp[i], dp[j] + 1);
		ans = max(ans, dp[i]);
	}
	printf("%d\n", ans);
}

