// BZOJ 3224 普通平衡树 (2018.2.17)
// Treap(树堆): 以随机值维护堆性质的二叉排序树
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 100002;

inline void getint(int &num){
	char ch; bool neg = 0;
	while(!isdigit(ch = getchar())) if(ch == '-') neg = 1;
	num = ch - '0';
	while(isdigit(ch = getchar())) num = num * 10 + ch - '0';
	if(neg) num = -num;
}

int n, opt, x;

struct Node{
	#define sz(x) ((x) ? (x)->size : 0)
	int val, pri, cnt, size;
	Node *lc, *rc;
	
	Node() {}
	Node(int v, int c, int s, Node *l, Node *r): val(v), cnt(c), size(s), lc(l), rc(r) {}
	
	inline void update() {size = sz(lc) + sz(rc) + cnt;}
} pool[MAXN << 1];

inline Node* newNode(int v, int c, int s, Node *l, Node *r){
	static int topp = 0;
	pool[topp] = Node(v, c, s, l, r);
	return &pool[topp++];
}

inline void rotate(Node *&cur, int dir){
	if(dir == 0){
		Node *o = cur->lc; cur->lc = o->rc, o->rc = cur;
		o->size = cur->size, cur->update(), cur = o;
	}
	else{
		Node *o = cur->rc; cur->rc = o->lc, o->lc = cur;
		o->size = cur->size, cur->update(), cur = o;
	}
}

inline void insert(Node *&cur, int v){
	if(cur == NULL) cur = newNode(v, 1, 1, NULL, NULL);
	else{
		cur->size++;
		if(v == cur->val) cur->cnt++;
		else if(v > cur->val){
			insert(cur->rc, v);
			if(cur->rc->pri < cur->pri) rotate(cur, 1);
		}
		else{
			insert(cur->lc, v);
			if(cur->lc->pri < cur->pri) rotate(cur, 0);
		}
	}
}

inline void erase(Node *&cur, int v){
	if(cur == NULL) return;
	if(v == cur->val){
		if(cur->cnt > 1) cur->cnt--, cur->size--;
		else{
			if(cur->lc && cur->rc){
				if(cur->lc->pri < cur->rc->pri) rotate(cur, 0), erase(cur, v);
				else rotate(cur, 1), erase(cur, v);  // 直接 "erase(cur->lc, v)" 会导致 size 没有更新 !!! 
			}
			else cur = cur->lc ? cur->lc : cur->rc;
		}
	}
	else{
		cur->size--;
		if(v > cur->val) erase(cur->rc, v);
		else erase(cur->lc, v);
	}
}

inline int rnk(Node *cur, int v){
	if(cur == NULL) return 1;  // 类比 "宗法树" 的 "return 2;" 操作 
	if(v == cur->val) return sz(cur->lc) + 1;
	else if(v < cur->val) return rnk(cur->lc, v);
	else return sz(cur->lc) + cur->cnt + rnk(cur->rc, v);
}

inline int kth(Node *cur, int k){
	if(cur == NULL) return 0;
	if(k <= sz(cur->lc)) return kth(cur->lc, k);
	else if(k > sz(cur->lc) + cur->cnt) return kth(cur->rc, k - sz(cur->lc) - cur->cnt);
	else return cur->val;
}

int main(){
	srand(19260817);
	getint(n);
	Node *root = NULL;
	while(n--){
		getint(opt), getint(x);
		if(opt == 1) insert(root, x);
		else if(opt == 2) erase(root, x);
		else if(opt == 3) printf("%d\n", rnk(root, x));
		else if(opt == 4) printf("%d\n", kth(root, x));
		else if(opt == 5) printf("%d\n", kth(root, rnk(root, x) - 1));
		else if(opt == 6) printf("%d\n", kth(root, rnk(root, x + 1)));
	}
	return 0;
}
