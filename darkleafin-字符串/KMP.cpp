// KMP �ַ���ƥ�� (2018.2.20)
// POJ 3461 Oulipo
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXWLEN = 10002;
const int MAXTLEN = 1000002;

int n, Wlen, Tlen, nxt[MAXWLEN];
char W[MAXWLEN], T[MAXTLEN];

int main(){
	scanf("%d", &n);
	while(n--){
		scanf("%s%s", W + 1, T + 1), Wlen = strlen(W + 1), Tlen = strlen(T + 1);
		nxt[1] = 0;
		for(register int i = 2, j = 0; i <= Wlen; i++){
			while(j && W[j + 1] != W[i]) j = nxt[j];  // ����ʧ��ǰ��״̬ 
			if(W[j + 1] == W[i]) j++;
			nxt[i] = j;  // Ԥ�������ͬǰ׺ 
		}
		int ans = 0;
		for(register int i = 1, j = 0; i <= Tlen; i++){
			while(j && W[j + 1] != T[i]) j = nxt[j];  // ����ʧ��ǰ��״̬ 
			if(W[j + 1] == T[i]) j++;
			if(j == Wlen) ans++, j = nxt[j];
		}
		printf("%d\n", ans);
	}
	return 0;
} 
