// Aho-Corasick Automaton (2018.2.26)
// 洛谷 3808 【模板】AC自动机（简单版）
// 给定 n 个模式串和 1 个文本串，求有多少个模式串在文本串里出现过 
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXLEN = 1000002;

int n;
char p[MAXLEN];

struct Aho_Corasick_Automaton{
	int trie[MAXLEN][26], cnt[MAXLEN], fail[MAXLEN], topp;
	queue<int> q;
	
	inline void insert(char *str){
		int len = strlen(str), cur = 0;
		for(register int i = 0; i < len; i++){
			int v = str[i] - 'a';
			if(!trie[cur][v]) trie[cur][v] = ++topp;
			cur = trie[cur][v];
		}
		cnt[cur]++;
	}  // 建立 Trie 
	
	inline void build_fail(){
		for(register int i = 0; i < 26; i++) if(trie[0][i]) fail[trie[0][i]] = 0, q.push(trie[0][i]);  // 根的子树 fail 指向根 
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(register int i = 0; i < 26; i++)
				if(trie[u][i]) fail[trie[u][i]] = trie[fail[u]][i], q.push(trie[u][i]);  // 子节点 fail 指向当前节点 fail 的同位子节点 
				else trie[u][i] = trie[fail[u]][i];  // 合并优化 
		}
	}
	
	inline int query(char *str){
		int len = strlen(str), cur = 0, res = 0;
		for(register int i = 0; i < len; i++){
			cur = trie[cur][str[i] - 'a'];
			for(register int j = cur; j && ~cnt[j]; j = fail[j]) res += cnt[j], cnt[j] = -1;  // 仅统计一次 
		}
		return res;
	}
} AC;

int main(){
	scanf("%d", &n);
	for(register int i = 1; i <= n; i++) scanf("%s", p), AC.insert(p);
	AC.build_fail();
	scanf("%s", p), printf("%d\n", AC.query(p));
	return 0;
}
