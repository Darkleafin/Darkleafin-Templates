// 扩展 KMP 算法 (2018.2.21)
/*
  S	|_______|____________________|______|_________|
	0       a                    i      p        Slen
	
	      T |______|_____________|______|_______|
	        0     p-i           i-a    p-a     Tlen
	            nxt[i-a]?
	
	设 S[a, p) 与 T[0, p - a) 匹配, 
	则当 S[p] != T[p - a] 时, 若 
		1) i + nxt[i - a] < p, 则 lcp[i] = nxt[i - a] 
		2) i + nxt[i - a] == p, 则从 S[p] 和 T[p - i] 开始往后暴力比较 
		3) i + nxt[i - a] > p, 则 lcp[i] = p - i 
*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;

char S[1000005], T[1000005];
int Slen, Tlen, nxt[1000005], lcp[1000005];

int main(){
	while(scanf("%s%s", S, T) != EOF){
		Slen = strlen(S), Tlen = strlen(T);
		nxt[0] = Tlen;
		for(register int i = 1, a = 0, p = 0; i < Tlen; i++){
			if(i + nxt[i - a] >= p){
				if(i > p) p = i;
				while(p < Tlen && T[p] == T[p - i]) p++;
				nxt[i] = p - i, a = i;
			}
			else nxt[i] = nxt[i - a];
		}
		for(register int i = 0, a = 0, p = 0; i < Slen; i++){
			if(i + nxt[i - a] >= p){
				if(i > p) p = i;
				while(p < Slen && S[p] == T[p - i]) p++;
				lcp[i] = p - i, a = i;
			}
			else lcp[i] = nxt[i - a];
		}
		for(register int i = 0; i < Slen - 1; i++) printf("%d ", lcp[i]);
		printf("%d\n", lcp[Slen - 1]);
	}
	return 0;
}
