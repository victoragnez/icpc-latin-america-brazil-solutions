#include<bits/stdc++.h>
using namespace std;

struct cmplx{
	double x, y;
	cmplx() : x(0), y(0) { }
	cmplx(double X, double Y) : x(X), y(Y) { }
};

inline cmplx operator+(cmplx a, cmplx b){
	return cmplx(a.x + b.x, a.y + b.y);
}
inline cmplx operator-(cmplx a, cmplx b){
	return cmplx(a.x - b.x, a.y - b.y);
}
inline cmplx operator*(cmplx a, cmplx b){
	return cmplx(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}
inline cmplx conj(cmplx a){
	return cmplx(a.x, -a.y);
}

int base = 1;
vector<cmplx> roots({ cmplx(0, 0), cmplx(1, 0) });
vector<int> rev = {0, 1};

const double pi = acos(-1.0);

void fft_pre(int nbase){
	rev.resize(1 << nbase);
	for(int i = 0; i < (1 << nbase); i++){
		rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
	}
	roots.resize(1 << nbase);
	while(base < nbase){
		double angle = 2 * pi / (1 << (base + 1));
		for(int i = 1 << (base - 1); i < (1 << base); i++){
			roots[i << 1] = roots[i];
			double angle_i = angle * (2 * i + 1 - (1 << base));
			roots[(i << 1) + 1] = cmplx(cos(angle_i), sin(angle_i));
		}
		base++;
	}
}

void fft(vector<cmplx> &a, int n = -1){
	if(n == -1){
		n = (int)a.size();
	}
	int zeros = __builtin_ctz(n);
	fft_pre(zeros);
	int shift = base - zeros;
	for(int i = 0; i < n; i++){
		if(i < (rev[i] >> shift)){
			swap(a[i], a[rev[i] >> shift]);
		}
	}
	for(int len = 1; len < n; len <<= 1){
		for(int i = 0; i < n; i += 2 * len){
			for(int j = i, k = i + len; j < i + len; j++, k++){
				cmplx z = a[k] * roots[k - i];
				a[k] = a[j] - z;
				a[j] = a[j] + z;
			}
		}
	}
}

const int MAXN = 1e5 + 1;
const int MAXM = MAXN * 26;
const int LOGM = 23;

vector<cmplx> fa(1 << LOGM);

void multiply(){
	fft_pre(LOGM);
	int sz = 1 << LOGM;
	fft(fa, sz);
	cmplx r(0, -0.25 / sz);
	for(int i = 0; i <= (sz >> 1); i++){
		int j = (sz - i) & (sz - 1);
		cmplx z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
		if(i != j)
			fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
		fa[i] = z;
	}
	fft(fa, sz);
}

char s[MAXN];

int main(){
	scanf("%s", s);
	int n = (int)strlen(s), ac = 0;
	
	fa[ac].x = 1;
	fa[MAXM - 1 - ac].y = 1;
	for(int i = 0; i < n; i++){
		ac += s[i] - 'a' + 1;
		fa[ac].x = 1;
		fa[MAXM - 1 - ac].y = 1;
	}
	
	multiply();
	
	int ans = 0;
	for(int i = MAXM; i < (int)fa.size(); i++)
		ans += (fa[i].x > 0.5);
	
	printf("%d\n", ans);
}


