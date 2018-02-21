// lxl & ddd 宗法树 (Balanced Tree) (2018.2.17)
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

struct file_io{
	#define isdigit(ch) ((ch) >= '0' && (ch) <= '9')
	char inbuf[1 << 25], *pin, outbuf[1 << 25], *pout;
	int stk[20];
	
	file_io(): pout(outbuf) {fread(pin = inbuf, 1, 1 << 25, stdin);}
	~file_io() {fwrite(outbuf, 1, pout - outbuf, stdout);}
	
	inline void getint(int &num){
		bool neg = 0; num = 0;
		while(!isdigit(*pin)) if(*pin++ == '-') neg = 1;
		while(isdigit(*pin)) num = num * 10 + *pin++ - '0';
		if(neg) num = -num;
	}
	
	inline void putint(int num){
		static int *v = stk;
		if(!num) *pout++ = '0';
		else{
			if(num < 0) *pout++ = '-', num = -num;
			for(; num; num /= 10) *v++ = num % 10;
			while(v != stk) *pout++ = *--v + '0';
		}
	}
	
	inline void nextline() {*pout++ = '\n';}
} fio;
#define getint(num) fio.getint(num)
#define putint(num) fio.putint(num)
#define nextline() fio.nextline()

int n, opt, x;

struct Node{
	int val, size;
	Node *lc, *rc;
	
	Node(): val(0), size(0), lc(NULL), rc(NULL) {}
	Node(int v, int s, Node *l, Node *r): val(v), size(s), lc(l), rc(r) {}
	
	inline bool isleaf() {return lc == NULL;}
	
	inline void update(){
		if(isleaf()) return;
		size = lc->size + rc->size;
		val = max(lc->val, rc->val);
	}
} pool[MAXN << 1];

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
		cur->rc->update();
	}
	else{  // Leftward rotate
		Node *l = cur->lc;
		cur->lc = cur->rc, cur->rc = cur->lc->rc;
		cur->lc->rc = cur->lc->lc, cur->lc->lc = l;
		cur->lc->update();
	}
}

inline void maintain(Node *cur){
	if(cur->isleaf()) return;
	if(cur->lc->size > cur->rc->size * ratio) rotate(cur, 0);
	if(cur->rc->size > cur->lc->size * ratio) rotate(cur, 1);
}

Node *stk[MAXN];
int tops = 0;

inline void insert(Node *&root, int v){
	if(root == NULL) {root = newNode(v, 1, NULL, NULL); return;}
	Node *cur = root;
	while(true){
		stk[++tops] = cur;
		if(cur->isleaf()){
			cur->lc = newNode(min(v, cur->val), 1, NULL, NULL);
			cur->rc = newNode(max(v, cur->val), 1, NULL, NULL);
			break;
		}
		if(v > cur->lc->val) cur = cur->rc;
		else cur = cur->lc;
	}
	while(tops) stk[tops]->update(), maintain(stk[tops--]);
}

inline void erase(Node *&root, int v){
	if(root == NULL) return;
	Node *cur = root, *fa = root;
	while(true){
		if(cur == NULL) return;
		if(cur->isleaf()){
			if(cur->val == v){
				if(cur == root) root = NULL;
				else if(cur == fa->lc) *fa = *fa->rc;
				else *fa = *fa->lc;
				break;
			}
		}
		else{
			stk[++tops] = cur;
			if(v > cur->lc->val) fa = cur, cur = cur->rc;
			else fa = cur, cur = cur->lc;
		}
	}
	while(tops) stk[tops]->update(), maintain(stk[tops--]);
}

inline int rnk(Node *cur, int v){
	int res = 0;
	while(true){
		if(cur->isleaf()){
			if(v > cur->val) return res + 2;
			return res + 1;
		}
		else{
			if(v > cur->lc->val) res += cur->lc->size, cur = cur->rc;
			else cur = cur->lc;
		}
	}
}

inline int kth(Node *cur, int k){
	while(true){
		if(cur->isleaf()) return cur->val;
		else{
			if(k > cur->lc->size) k -= cur->lc->size, cur = cur->rc;
			else cur = cur->lc;
		}
	}
}

int main(){
	getint(n);
	Node *root = NULL;
	while(n--){
		getint(opt), getint(x);
		if(opt == 1) insert(root, x);
		else if(opt == 2) erase(root, x);
		else if(opt == 3) putint(rnk(root, x)), nextline();
		else if(opt == 4) putint(kth(root, x)), nextline();
		else if(opt == 5) putint(kth(root, rnk(root, x) - 1)), nextline();
		else if(opt == 6) putint(kth(root, rnk(root, x + 1))), nextline();
	}
	return 0;
}
