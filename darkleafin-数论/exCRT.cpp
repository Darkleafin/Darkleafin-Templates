// 扩展中国剩余定理 (2018.2.20) 
/*
	POJ 2891 Strange Way to Express Integers
	 
	合并两个同余方程 
		x ≡ a1 (mod m1)
		x ≡ a2 (mod m2)
	该方程等价于 
		x = a1 + m1 * p
		x = a2 + m2 * q
	可化为 
		m1 * (-p) + m2 * q = a1 - a2
	令 d = exgcd(m1, m2, x, y), 则 
	当且仅当 d | (a1 - a2) 时可合并,
		此时令 p = -x * (a1 - a2) / d,
		合并式为 x ≡ a1 + m1 * p (mod LCM(m1, m2)).
*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

int k;
ll a[100002], r[100002];

inline ll exgcd(ll a, ll b, ll &x, ll &y){
	if(!b) return x = 1, y = 0, a;
	ll d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

int main(){
	while(scanf("%d", &k) != EOF){
		for(register int i = 1; i <= k; i++) scanf("%lld%lld", a + i, r + i);
		ll M = a[1], R = r[1], x, y, d;
		bool nosol = 0;
		for(register int i = 2; i <= k; i++){
			d = exgcd(M, a[i], x, y);
			if((R - r[i]) % d) {puts("-1"), nosol = 1; break;}
			x = (R - r[i]) / d * (-x % a[i]) % a[i];  // Divide first to avoid overflowing
			R += M * x;
			M = M / d * a[i];  // Divide first to avoid overflowing
			R %= M;
		}
		if(!nosol) printf("%lld\n", R < 0 ? R + M : R);
	}
	return 0;
}
