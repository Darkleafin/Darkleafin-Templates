// 左偏树 (2018.3.3)
// 洛谷 3377 【模板】左偏树（可并堆）
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 100005;

inline void getint(int &num){
	char ch;
	while(!isdigit(ch = getchar()));
	num = ch - '0';
	while(isdigit(ch = getchar())) num = num * 10 + ch - '0';
}

int N, M, a[MAXN], topp = 0;

struct Node{
	int val, dist;
	Node *lc, *rc, *fa;
	bool del;
} pool[MAXN], *nul = pool;  // Avoid using NULL

inline void build(int *a, int n){
	nul->val = nul->dist = -1, nul->del = 1;
	for(register int i = 1; i <= n; i++){
		pool[i].val = a[i], pool[i].dist = 0;
		pool[i].lc = pool[i].rc = nul, pool[i].fa = &pool[i];
		pool[i].del = 0;
	}
}

inline Node* find(Node *u) {while(u->fa != u) u = u->fa; return u;}

inline Node* merge(Node *u, Node *v){
	if(u == nul) return v;
	if(v == nul) return u;
	if(u->val == v->val ? u > v : u->val > v->val) swap(u, v);
	u->rc = merge(u->rc, v), u->rc->fa = u;
	if(u->lc->dist < u->rc->dist) swap(u->lc, u->rc);
	u->dist = u->rc->dist + 1;
	return u;
}

inline void pop(Node *u){
	Node *r = merge(u->lc, u->rc);
	r->fa = r, u->del = 1;
}

int main(){
	getint(N), getint(M);
	for(register int i = 1; i <= N; i++) getint(a[i]);
	build(a, N);
	for(register int i = 1; i <= M; i++){
		int opt, x, y; getint(opt);
		if(opt == 1){
			getint(x), getint(y);
			if(pool[x].del || pool[y].del) continue;
			Node *rx = find(&pool[x]), *ry = find(&pool[y]);
			if(rx == ry) continue;
			merge(rx, ry);
		}
		else if(opt == 2){
			getint(x);
			if(pool[x].del) {puts("-1"); continue;}
			Node *rx = find(&pool[x]);
			printf("%d\n", rx->val);
			pop(rx);
		}
	}
	return 0;
}
