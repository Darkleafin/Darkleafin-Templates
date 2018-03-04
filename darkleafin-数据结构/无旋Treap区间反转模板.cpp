// 无旋 Treap 区间反转 (2018.3.4)
// BZOJ 3223 文艺平衡树
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream> 
#include<algorithm>
#define MAXN 100005
using namespace std;
typedef pair<int, int> PII;

inline void getint(int &num){
	char ch;
	while(!isdigit(ch = getchar()));
	num = ch - '0';
	while(isdigit(ch = getchar())) num = num * 10 + ch - '0';
}

int n, m, l, r;

struct Treap{
	int root, val[MAXN], wt[MAXN], size[MAXN], lc[MAXN], rc[MAXN], topp;
	bool rev[MAXN];
	
	inline void update(int u) {size[u] = size[lc[u]] + size[rc[u]] + 1;}
	
	inline void pushdown(int u){
		if(rev[u]){
			swap(lc[u], rc[u]);
			rev[lc[u]] ^= 1, rev[rc[u]] ^= 1;
			rev[u] = 0;
		}
	}
	
	inline PII split(int u, int pos){
		pushdown(u);
		if(!pos) return make_pair(0, u);
		int l = lc[u], r = rc[u];
		if(pos == size[l]) return lc[u] = 0, update(u), make_pair(l, u);
		else if(pos == size[l] + 1) return rc[u] = 0, update(u), make_pair(u, r);
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
		if(!u || !v) return pushdown(u | v), u | v;
		if(wt[u] < wt[v]) return pushdown(u), rc[u] = merge(rc[u], v), update(u), u;
		else return pushdown(v), lc[v] = merge(u, lc[v]), update(v), v;
	}
	
	inline void build(int n){
		int *stk = new int[MAXN], tops = 0; stk[0] = 0, topp = n;
		for(register int i = 1; i <= n; i++) val[i] = i, wt[i] = rand(), size[i] = 1, lc[i] = rc[i] = 0, rev[i] = 0;
		for(register int i = 1; i <= n; i++){
			int o = 0;
			while(tops && wt[i] < wt[stk[tops]]) update(o = stk[tops--]);
			rc[stk[tops]] = i, lc[i] = o;
			stk[++tops] = i;
		}
		while(tops) update(stk[tops--]);
		root = stk[1];
		delete []stk;
	}
	
	inline void reverse(int l, int r){
		PII rootr = split(root, r), rootl = split(rootr.first, l - 1);
		rev[rootl.second] ^= 1;
		root = merge(merge(rootl.first, rootl.second), rootr.second);
	}
	
	inline void inorder(int u){
		pushdown(u);
		if(lc[u]) inorder(lc[u]);
		printf("%d ", val[u]);
		if(rc[u]) inorder(rc[u]);
	}
} treap;

int main(){
	getint(n), getint(m);
	treap.build(n);
	for(register int i = 1; i <= m; i++){
		getint(l), getint(r);
		treap.reverse(l, r);
	}
	treap.inorder(treap.root), puts("");
	return 0;
}
