// 块状链表 (2018.3.2) 
// BZOJ 1507 [NOI 2003] Editor
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int blsize = 1448;  // sqrt(1024 * 1024 * 2)
const int MAXSIZE = (blsize << 1) + 2;

int T, n, cs = 0, topbin = 0;
char opt[10], s[2100000];

inline void readstr(char str[], int len){
	char *p = str;
	while(p - str < len) gets(p), p += strlen(p);
}

struct Node{
	char val[MAXSIZE];
	int size;
	Node *pre, *suc;
	
	inline void clear() {size = 0, pre = suc = NULL;}
} pool[MAXSIZE], *bin[MAXSIZE];

inline Node* newNode(){
	static int topp = 0;
	Node *cur = topbin ? bin[--topbin] : &pool[topp++];
	return cur->clear(), cur;
}

inline void delNode(Node *cur) {bin[topbin++] = cur;}

inline void split(Node *cur, int pos){
	Node *o = newNode();
	o->size = cur->size - pos, cur->size = pos;
	o->suc = cur->suc, o->pre = cur, cur->suc = o;
	if(o->suc) o->suc->pre = o;
	memcpy(o->val, cur->val + cur->size, sizeof(char) * o->size);
}

inline void merge(Node *cur, Node *o){
	memcpy(cur->val + cur->size, o->val, sizeof(char) * o->size);
	cur->size += o->size;
	cur->suc = o->suc;
	if(cur->suc) cur->suc->pre = cur;
	delNode(o);
}

inline void maintain(Node *cur){
	if(cur->size >= blsize << 1) split(cur, cur->size >> 1);
	else if(cur->pre && cur->pre->size + cur->size < blsize << 1) merge(cur->pre, cur);
	else if(cur->suc && cur->size + cur->suc->size < blsize << 1) merge(cur, cur->suc);
}

inline void Insert(Node *cur, int pos, char *str, int len){
	while(pos > cur->size) pos -= cur->size, cur = cur->suc;
	split(cur, pos); Node *o = cur->suc;
	for(register int i = 0; i < len; i++){
		if(cur->size == blsize) cur->suc = newNode(), cur->suc->pre = cur, cur = cur->suc;
		cur->val[cur->size++] = str[i];
	}
	cur->suc = o, o->pre = cur, maintain(o);
}

inline void Delete(Node *cur, int pos, int len){
	while(pos > cur->size) pos -= cur->size, cur = cur->suc;
	split(cur, pos); Node *o = cur->suc;
	while(len > o->size) delNode(o), len -= o->size, o = o->suc;
	split(o, len), delNode(o), o = o->suc;
	cur->suc = o, o->pre = cur, maintain(o);
}

inline void Get(Node *cur, int pos, int len){
	while(pos > cur->size) pos -= cur->size, cur = cur->suc;
	while(len--){
		if(pos == cur->size) cur = cur->suc, pos = 0;
		putchar(cur->val[pos++]);
	}
	putchar('\n');
}

int main(){
	scanf("%d", &T);
	Node *head = newNode();
	while(T--){
		scanf("%s", opt);
		if(opt[0] == 'M') scanf("%d", &cs);  // Reset the cursor
		else if(opt[0] == 'I') scanf("%d", &n), readstr(s, n), Insert(head, cs, s, n);
		else if(opt[0] == 'D') scanf("%d", &n), Delete(head, cs, n);
		else if(opt[0] == 'G') scanf("%d", &n), Get(head, cs, n);
		else if(opt[0] == 'P') cs--;  // Shift the cursor to left
		else if(opt[0] == 'N') cs++;  // Shift the cursor to right
	}
	return 0;
}
