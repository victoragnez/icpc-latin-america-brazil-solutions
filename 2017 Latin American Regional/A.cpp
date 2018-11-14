#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;

int cmp(double x, double y=0, double tol = EPS){
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

double abs(point a){
	return sqrt(a*a);
}
double dist(point a, point b){
	return abs(a-b);
}
int ccw(point a, point b, point c){
	return cmp((b-a) % (c-a));
}
bool between(point a, point b, point c){
	return ccw(a,b,c)==0 && cmp((a-b) * (c-b)) <= 0;
}
double angle(point u, point v){
	return atan2(u%v,u*v);
}

point pivot;
bool radialcomp(point p, point q){
	point P = p - pivot, Q = q - pivot;
	double R = P % Q;
	if(cmp(R) != 0)
		return R > 0;
	return cmp(P * P, Q * Q) < 0;
}

point inter(point p, point q, point r, point s){
	point a = q - p, b = s - r, c = point(p % q, r % s);
	return point(point(a.x, b.x) % c, point(a.y, b.y) % c) / (a%b);
}

bool has_inter(point p, point q, point r, point s){
	return ccw(p, q, r) * ccw(p, q, s) <= 0 && ccw(r, s, p) * ccw(r, s, q) <= 0;
}

const int N = 14;
const double inf = 1e20;
int n, k;
int L[N], R[N];
double dp[1<<N][N], dd[N][N];
vector<point> v[N], vm[N];

double solve(int mask, int pos){
	if(mask == 0)
		return R[pos];
	
	if(cmp(dp[mask][pos]) >= 0)
		return dp[mask][pos];
	
	double best = inf;
	for(int i = 0; i < n; i++){
		if(mask & (1<<i)){
			best = min(best, dd[pos][i] + solve(mask^(1<<i), i)); 
		}
	}

	if(cmp(best,inf) >= 0)
		best = 0;
	return dp[mask][pos] = best; 
}

double get(int _a, int _b){
	vector<point> a = v[_a], b = vm[_b], c;
	point pa = *min_element(a.begin(), a.end());
	point pb = *min_element(b.begin(), b.end());
	int pi = 0, pj = 0, na = (int)a.size(), nb = (int)b.size();
	point p = pa + pb;
	
	//Minkowski sum
	for(int i = 0; i < (na + nb); i++){
		if(pi == na){
			p = p + (b[(pj+1) % nb] - b[pj]);
			pj++;
		}
		else if(pj == nb){
			p = p + (a[(pi+1) % na] - a[pi]);
			pi++;
		}
		else{
			if((b[(pj+1) % nb] - b[pj]) % (a[(pi+1) % na] - a[pi]) > 0){
				p = p + (b[(pj+1) % nb] - b[pj]);
				pj++;
			}
			else{
				p = p + (a[(pi+1) % na] - a[pi]);
				pi++;
			}
		}
		c.emplace_back(p);
	}

	for(int i = 0; i < (int)c.size(); i++)
		if(has_inter(point(0,0), point(1e9 + 10,0), c[i], c[(i+1) % c.size()]))
			return inter(point(0,0), point(1e9 + 10,0), c[i], c[(i+1) % c.size()]).x;

	assert(0);
	return -1;
}


int main(){
	for(int i = 0; i < (1<<N); i++)
		for(int j = 0; j < N; j++)
			dp[i][j] = -1;
			
	scanf("%d ", &n);
	for(int i = 0; i < n; i++){
		scanf("%d ", &k);
		for(int j = 0; j < k; j++){
			int x, y;
			scanf("%d %d", &x, &y);
			
			v[i].emplace_back(point(x,y));
			vm[i].emplace_back(point(0,0) - v[i].back());
			
			L[i] = min(L[i], x);
			R[i] = max(R[i], x);
		}
	}
	
	for(int i = 0; i < n; i++){
		pivot = *min_element(v[i].begin(), v[i].end());
		sort(v[i].begin(), v[i].end(), radialcomp);
		
		pivot = *min_element(vm[i].begin(), vm[i].end());
		sort(vm[i].begin(), vm[i].end(), radialcomp);
	}
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j)
				continue;
			dd[i][j] = get(i, j);
		}
	}

	double ans = inf;
	int all = (1<<n)-1;
	for(int i = 0; i < n; i++)
		ans = min(ans, -L[i] + solve(all^(1<<i), i));
	
	printf("%.3lf\n", ans);
}

