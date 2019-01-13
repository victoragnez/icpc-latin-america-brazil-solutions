#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int cmp(double x, double y = 0, double tol = EPS){
	return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct point{
	double x, y;
	point() : x(0), y(0){}
	point(double X, double Y) : x(X), y(Y){}
	int cmp(const point a) const {
		if(::cmp(x, a.x))
			return ::cmp(x, a.x);
		return ::cmp(y, a.y);
	}
	point operator+(point a){
		return point(x+a.x, y+a.y);
	}
	point operator-(point a){
		return point(x-a.x, y-a.y);
	}
	point operator/(double a){
		return point(x/a, y/a);
	}
	double operator*(point a){
		return x*a.x + y*a.y;
	}
	double operator%(point a){
		return x*a.y - y*a.x;
	}
	bool operator==(const point a) const {
		return cmp(a) == 0;
	}
	bool operator<(const point a) const {
		return cmp(a) < 0;
	}
};
int ccw(point a, point b, point c){
	return cmp((b - a) % (c - a));
}

const int MAXN = 1e5 + 1;
const double inf = 1e30;
int n;
point vet[MAXN];
double dp[MAXN][2][2][2][2][2];
point a, b;

double solve(int i, int j, int k, int p, int pri, int sec){
	if(i == n){
		point prev1 = (vet[i - 1] + (j ? b : a)) / 2;
		point prev2 = (vet[i - 2] + (k ? b : a)) / 2;
		
		point nxt1 = (vet[0] + (pri ? b : a)) / 2;
		point nxt2 = (vet[1] + (sec ? b : a)) / 2;
		
		if(p != 0 && ccw(prev2, prev1, nxt1) >= 0 && ccw(prev1, nxt1, nxt2) >= 0)
			return 0;

		return inf;
	}
	
	double & ret = dp[i][j][k][p][pri][sec];
	if(cmp(ret, inf) != 0)
		return ret;

	point pa = (vet[i] + a) / 2;
	point pb = (vet[i] + b) / 2;
	point prev1 = (vet[i - 1] + (j ? b : a)) / 2;
	point prev2 = (vet[i - 2] + (k ? b : a)) / 2;
	point pt1 = (vet[0] + (pri ? b : a)) / 2;

	if(ccw(prev2, prev1, pa) >= 0 && ccw(pt1, prev1, pa) >= 0)
		ret = min(ret, solve(i + 1, 0, j, (p || ccw(prev2, prev1, pa)), pri, sec) + ((prev1 - pt1) % (pa - pt1)));
	
	if(ccw(prev2, prev1, pb) >= 0 && ccw(pt1, prev1, pb) >= 0)
		ret = min(ret, solve(i + 1, 1, j, (p || ccw(prev2, prev1, pb)), pri, sec) + ((prev1 - pt1) % (pb - pt1)));
	
	return ret;
}

double run(){
	for(int i = 0; i < MAXN; i++){
		vector<int> boolVals( { 0, 1 } );
		for(int j : boolVals)
			for(int k : boolVals)
				for(int l : boolVals)
					for(int m : boolVals)
						for(int o : boolVals)
							dp[i][j][k][l][m][o] = inf;
	}

	double ret = inf;
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			ret = min(ret, solve(2, i, j, 0, j, i));

	return ret / 2;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		vet[i] = point(x, y);
	}
	int xa, ya, xb, yb;
	scanf("%d%d%d%d", &xa, &ya, &xb, &yb);
	a = point(xa, ya);
	b = point(xb, yb);

	double ans = run();
	reverse(vet, vet + n);
	ans = min(ans, run());

	printf("%.3f\n", ans);
}

