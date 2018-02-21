// lxl & ddd 宗法树 (Balanced Tree) (2018.2.11)
// BZOJ 3224 普通平衡树 
/*
	每个节点要么没有子树, 要么有 2 个子树 
	叶节点保存值, 非叶节点保存 2 个子树值的较大值 
*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 100002;
const int ratio = 4;

template<typename T>
inline void getint(T &num){
	char ch; bool neg = 0;
	while(!isdigit(ch = getchar())) if(ch == '-') neg = 1;
	num = ch - '0';
	while(isdigit(ch = getchar())) num = num * 10 + ch - '0';
	if(neg) num = -num;
}

int n, opt, x;

struct Node{
	int val, size;
	Node *lc, *rc;
	
	Node(): val(0), size(0), lc(NULL), rc(NULL) {}
	Node(int v, int s, Node *l, Node *r): val(v), size(s), lc(l), rc(r) {}
	
	inline bool isleaf() {return lc == NULL;}
	
	inline void pushup(){
		if(isleaf()) return;
		size = lc->size + rc->size;
		val = max(lc->val, rc->val);
	}
} pool[MAXN << 2];

inline Node* newNode(int v, int s, Node *l, Node *r){
	static int topp = 0;
	pool[topp] = Node(v, s, l, r);
	return &pool[topp++];
}

inline void rotate(Node *cur, int dir){
	if(dir == 0){  // Rightward rotate
		Node *r = cur->rc;
		cur->rc = cur->lc, cur->lc = cur->rc->lc;
		cur->rc->lc = cur->rc->rc, cur->rc->rc = r;
		cur->rc->pushup();
	}
	else{  // Leftward rotate
		Node *l = cur->lc;
		cur->lc = cur->rc, cur->rc = cur->lc->rc;
		cur->lc->rc = cur->lc->lc, cur->lc->lc = l;
		cur->lc->pushup();
	}
}

inline void maintain(Node *cur){
	if(cur->isleaf()) return;
	if(cur->lc->size > cur->rc->size * ratio) rotate(cur, 0);
	if(cur->rc->size > cur->lc->size * ratio) rotate(cur, 1);
}

inline void insert(Node *&cur, int v){
	if(cur == NULL) cur = newNode(v, 1, NULL, NULL);
	else{
		if(cur->isleaf()){
			cur->lc = newNode(min(v, cur->val), 1, NULL, NULL);
			cur->rc = newNode(max(v, cur->val), 1, NULL, NULL);
		}
		else{
			if(v > cur->lc->val) insert(cur->rc, v);
			else insert(cur->lc, v);
		}
		cur->pushup();
		maintain(cur);
	}
}

inline void erase(Node *&cur, Node *fa, int v){
	if(cur->isleaf()){
		if(cur->val == v){
			if(cur == fa) cur = NULL;
			else if(cur == fa->lc) *fa = *fa->rc;
			else *fa = *fa->lc;
		}
	}
	else{
		if(v > cur->lc->val) erase(cur->rc, cur, v);
		else erase(cur->lc, cur, v);
		cur->pushup();
		maintain(cur);
	}
}

inline int rnk(Node *cur, int v){
	if(cur->isleaf()){
		if(v > cur->val) return 2;
		return 1;
	}
	else{
		if(v > cur->lc->val) return rnk(cur->rc, v) + cur->lc->size;
		else return rnk(cur->lc, v);
	}
}

inline int kth(Node *cur, int k){
	if(cur->isleaf()) return cur->val;
	else{
		if(k > cur->lc->size) return kth(cur->rc, k - cur->lc->size);
		else return kth(cur->lc, k);
	}
}

int main(){
	getint(n);
	Node *root = NULL;
	while(n--){
		getint(opt), getint(x);
		if(opt == 1) insert(root, x);
		else if(opt == 2) erase(root, root, x);
		else if(opt == 3) printf("%d\n", rnk(root, x));
		else if(opt == 4) printf("%d\n", kth(root, x));
		else if(opt == 5) printf("%d\n", kth(root, rnk(root, x) - 1));
		else if(opt == 6) printf("%d\n", kth(root, rnk(root, x + 1)));
	}
	return 0;
}
