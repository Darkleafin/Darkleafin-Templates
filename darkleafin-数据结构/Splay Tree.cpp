// Splay Tree (Balanced Binary Search Tree) (2018.2.15)
// BZOJ 3223 文艺平衡树 
/*
	rotate(cur, dir):
		右旋(dir == 0): 设 cur 的左孩子为 o
			(1) 将 o 的右子树连在 cur 的左子树上 
			(2) 将 o 连在 cur 的父亲的左/右子树上 
			(3) 将 cur 连在 o 的右子树上 
		左旋(dir == 1): 设 cur 的右孩子为 o 
			(1) 将 o 的左子树连在 cur 的右子树上 
			(2) 将 o 连在 cur 的父亲的左/右子树上 
			(3) 将 cur 连在 o 的左子树上 
	splay(cur, tf):
		Zig Step: 当 cur 的父节点离目标父节点 tf 只差一层时, 旋转父节点 
		Zig-zig Step: 若 cur 与其父节点子树情况相同, 先旋转爷爷节点, 再旋转父节点 
		Zig-zag Step: 若 cur 与其父节点子树情况相反, 旋转父节点不同方向各一次 
*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 100002;

inline void getint(int &num){
	char ch;
	while(!isdigit(ch = getchar()));
	num = ch - '0';
	while(isdigit(ch = getchar())) num = num * 10 + ch - '0';
}

int n, m, a[MAXN];

struct Splay_Tree{
	struct Node{
		#define islc(cur) ((cur) == (cur)->fa->ch[0])
		#define isrc(cur) ((cur) == (cur)->fa->ch[1])
		int val, size, rev;
		Node *fa, *ch[2];
		
		Node(): val(0), size(0), rev(0), fa(NULL) {ch[0] = ch[1] = NULL;}
		Node(int v, int s, Node *f, Node *l, Node *r): val(v), size(s), rev(0), fa(f) {ch[0] = l, ch[1] = r;}
		
		inline void update() {size = (ch[0] ? ch[0]->size : 0) + (ch[1] ? ch[1]->size : 0) + 1;}
		
		inline void pushdown(){
			if(rev){
				swap(ch[0], ch[1]);
				if(ch[0]) ch[0]->rev ^= 1;
				if(ch[1]) ch[1]->rev ^= 1;
				rev = 0;
			}
		}
	} pool[MAXN << 2], *root;
	
	inline Node* newNode(int v, int s, Node *f, Node *l, Node *r){
		static int topp = 0;
		pool[topp] = Node(v, s, f, l, r);
		return &pool[topp++];
	}
	
	inline Node* build(int *sorted, int l, int r, Node *fa = NULL){
		int smid = l + r >> 1;
		Node *cur = newNode(sorted[smid], 0, fa, NULL, NULL);
		if(l < smid) cur->ch[0] = build(sorted, l, smid - 1, cur);
		if(smid < r) cur->ch[1] = build(sorted, smid + 1, r, cur);
		return cur->update(), cur;
	}
	
	inline void rotate(Node *cur, int dir){
		Node *o = cur->ch[dir];
		if(!o) return;
		cur->pushdown(), o->pushdown();
		
		cur->ch[dir] = o->ch[dir ^ 1];
		if(o->ch[dir ^ 1]) o->ch[dir ^ 1]->fa = cur;
		
		o->fa = cur->fa;
		if(!cur->fa) root = o;
		else if(islc(cur)) cur->fa->ch[0] = o;
		else cur->fa->ch[1] = o;
		
		o->ch[dir ^ 1] = cur, cur->fa = o;
		cur->update(), o->update();
	}
	
	inline void splay(Node *cur, Node *tf){
		while(cur->fa != tf){
			if(cur->fa->fa == tf) if(islc(cur)) rotate(cur->fa, 0); else rotate(cur->fa, 1);
			else if(islc(cur) && islc(cur->fa)) rotate(cur->fa->fa, 0), rotate(cur->fa, 0);
			else if(isrc(cur) && isrc(cur->fa)) rotate(cur->fa->fa, 1), rotate(cur->fa, 1);
			else if(islc(cur) && isrc(cur->fa)) rotate(cur->fa, 0), rotate(cur->fa, 1);
			else rotate(cur->fa, 1), rotate(cur->fa, 0);
		}
	}
	
	inline Node* find(int id){
		Node *p = root;
		while(p){
			p->pushdown();
			int lsize = p->ch[0] ? p->ch[0]->size + 1 : 1;
			if(id < lsize) p = p->ch[0];
			else if(id > lsize) id -= lsize, p = p->ch[1];
			else return p;
		}
		return NULL;
	}
	
	inline void reverse(int l, int r){
		if(l >= r) return;
		Node *pl = find(l - 1), *pr = find(r + 1);
		if(pl && pr) {splay(pl, NULL), splay(pr, pl); if(pr->ch[0]) pr->ch[0]->rev ^= 1;}
		else if(pr) {splay(pr, NULL); if(pr->ch[0]) pr->ch[0]->rev ^= 1;}
		else if(pl) {splay(pl, NULL); if(pl->ch[1]) pl->ch[1]->rev ^= 1;}
		else if(root) root->rev ^= 1;
	}
	
	inline void inorder(Node *cur){
		cur->pushdown();
		if(cur->ch[0]) inorder(cur->ch[0]);
		printf("%d ", cur->val);
		if(cur->ch[1]) inorder(cur->ch[1]);
	}
} splay;

int main(){
	getint(n), getint(m);
	for(register int i = 1; i <= n; i++) a[i] = i;
	splay.root = splay.build(a, 1, n);
	for(register int i = 1; i <= m; i++){
		int l, r;
		getint(l), getint(r);
		splay.reverse(l, r);
	}
	splay.inorder(splay.root); puts("");
	return 0;
}
