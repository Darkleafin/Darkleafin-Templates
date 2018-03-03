// 无旋 Treap (2018.3.3)
// BZOJ 3224 普通平衡树 
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#define MAXN 100005
#define INFINT 0x3f3f3f3f
using namespace std;
typedef pair<int, int> PII;

inline void getint(int &num){
	char ch; bool neg = 0;
	while(!isdigit(ch = getchar())) if(ch == '-') neg = 1;
	num = ch - '0';
	while(isdigit(ch = getchar())) num = num * 10 + ch - '0';
	if(neg) num = -num;
}

int n, opt, x;

struct Treap{
	int root, val[MAXN], wt[MAXN], size[MAXN], lc[MAXN], rc[MAXN], topp;
	
	inline void update(int u) {size[u] = size[lc[u]] + size[rc[u]] + 1;}
	
	inline PII split(int u, int pos){
		if(!pos) return make_pair(0, u);
		int l = lc[u], r = rc[u];
		if(pos == size[l]) return lc[u] = 0, update(u), make_pair(l, u);  // Exactly cut off whole left subtree
		else if(pos == size[l] + 1) return rc[u] = 0, update(u), make_pair(u, r);  // Exactly cut off whole right subtree
		else if(pos < size[l]){
			PII roots = split(l, pos);
			return lc[u] = roots.second, update(u), make_pair(roots.first, u);
		}
		else{
			PII roots = split(r, pos - size[l] - 1);
			return rc[u] = roots.first, update(u), make_pair(u, roots.second);
		}
	}
	
	inline int merge(int u, int v){
		if(!u || !v) return u | v;
		if(wt[u] < wt[v]) return rc[u] = merge(rc[u], v), update(u), u;
		else return lc[v] = merge(u, lc[v]), update(v), v;
	}
	
	inline int rnk(int x){
		int u = root, delta = 0, res = INFINT;
		while(u){
			if(x == val[u]) res = min(res, delta + size[lc[u]] + 1);
			if(x > val[u]) delta += size[lc[u]] + 1, u = rc[u];
			else u = lc[u];
		}
		return res < INFINT ? res : delta;
	}
	
	inline int kth(int k){
		int u = root;
		while(u){
			if(size[lc[u]] + 1 == k) return val[u];
			if(size[lc[u]] + 1 > k) u = lc[u];
			else k -= size[lc[u]] + 1, u = rc[u];
		}
	}
	
	inline int pred(int x){
		int u = root, res = -INFINT;
		while(u){
			if(val[u] < x) res = max(res, val[u]), u = rc[u];
			else u = lc[u];
		}
		return res;
	}
	
	inline int succ(int x){
		int u = root, res = INFINT;
		while(u){
			if(val[u] > x) res = min(res, val[u]), u = lc[u];
			else u = rc[u];
		}
		return res;
	}
	
	inline void insert(int x){
		int k = rnk(x); PII roots = split(root, k);
		val[++topp] = x, wt[topp] = rand(), size[topp] = 1;
		root = merge(merge(roots.first, topp), roots.second);
	}
	
	inline void erase(int x){
		int k = rnk(x); PII rootr = split(root, k), rootl = split(rootr.first, k - 1);
		root = merge(rootl.first, rootr.second);
	}
} treap;

int main(){
	srand(19260817), getint(n);
	for(register int i = 1; i <= n; i++){
		getint(opt), getint(x);
		if(opt == 1) treap.insert(x);
		else if(opt == 2) treap.erase(x);
		else if(opt == 3) printf("%d\n", treap.rnk(x));
		else if(opt == 4) printf("%d\n", treap.kth(x));
		else if(opt == 5) printf("%d\n", treap.pred(x));
		else if(opt == 6) printf("%d\n", treap.succ(x));
	}
	return 0;
}
