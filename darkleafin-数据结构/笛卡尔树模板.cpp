// 笛卡尔树 (2018.3.2)
// POJ 2201 Cartesian Tree
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;

inline void getint(int &num){
	char ch; bool neg = 0;
	while(!isdigit(ch = getchar())) if(ch == '-') neg = 1;
	num = ch - '0';
	while(isdigit(ch = getchar())) num = num * 10 + ch - '0';
	if(neg) num = -num;
}

int N, tops = 0;
int fa[50002], lc[50002], rc[50002];

struct Node{
	int id, val, wt;
	Node *lc, *rc, *fa;
	
	inline bool operator < (const Node &node2) const {return val < node2.val;}
} CT[50002], *stk[50002];

inline Node* build(Node *CT, int Size){
	for(register int i = 1; i <= Size; i++){
		Node *o = NULL;
		while(tops && CT[i].wt < stk[tops]->wt) o = stk[tops--];  // Maintain the monotonous stack
		CT[i].lc = o, CT[i].fa = stk[tops];
		if(o) o->fa = &CT[i];
		if(stk[tops]) stk[tops]->rc = &CT[i];  // Redirect the pointers of relationship
		stk[++tops] = &CT[i];
	}
	return stk[1];
}

int main(){
	getint(N);
	for(register int i = 1; i <= N; i++) getint(CT[i].val), getint(CT[i].wt), CT[i].id = i;
	sort(CT + 1, CT + N + 1);  // BST indexes must be ascending
	Node *root = build(CT, N);
	for(register int i = 1; i <= N; i++){
		fa[CT[i].id] = CT[i].fa ? CT[i].fa->id : 0;
		lc[CT[i].id] = CT[i].lc ? CT[i].lc->id : 0;
		rc[CT[i].id] = CT[i].rc ? CT[i].rc->id : 0;
	}
	puts("YES");  // Must have solution
	for(register int i = 1; i <= N; i++) printf("%d %d %d\n", fa[i], lc[i], rc[i]);
	return 0;
}
