// ��׺���� (Suffix Array, SA) (2018.2.23)
// TYVJ 1860 (JoyOI)
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 200005;

int n, SA[MAXN], rnk[MAXN], ht[MAXN];
char s[MAXN];

inline void buildSA(int m){
	int *x = new int[MAXN], *y = new int[MAXN], *cnt = new int[MAXN];
	for(register int i = 0; i < m; i++) cnt[i] = 0;  // ���Ͱ, ���л������� 
	for(register int i = 0; i < n; i++) cnt[x[i] = s[i]]++;  // x[] Ϊ�� i λ�ַ�����Դ�С 
	for(register int i = 1; i < m; i++) cnt[i] += cnt[i - 1];  // �ҵ�ÿ��ֵ�����Ŀ�ʼλ�� 
	for(register int i = n - 1; i >= 0; i--) SA[--cnt[x[i]]] = i;   // ��ÿ����׺����һλ�ȶ�����Ľ������ SA[] 
	for(register int k = 1; k <= n; k <<= 1){  // ���������ؼ���֮��ľ��� k 
		int p = 0;
		for(register int i = n - k; i < n; i++) y[p++] = i;  // ��ĩβ�ڶ��ؼ��ֳ�����Χ n �Ŀ��� 0, ��Ϊ 0 ��С���Է�����ǰ�� 
		for(register int i = 0; i < n; i++) if(SA[i] >= k) y[p++] = SA[i] - k;  // SA Ϊ��ǰ�ڶ��ؼ����ź����λ��, ��ȥ k ���ö�Ӧ�ĵ�һ�ؼ���, ������ y[] ��Ӧ�Ĵ��Ͱ��ڶ��ؼ����ź����� 
		for(register int i = 0; i < m; i++) cnt[i] = 0;  // ���л������� 
		for(register int i = 0; i < n; i++) cnt[x[y[i]]]++;  // ԭ���� i �� y[i] ����, ��֤�ڶ��ؼ����ȶ� 
		for(register int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
		for(register int i = n - 1; i >= 0; i--) SA[--cnt[x[y[i]]]] = y[i];  // ���� SA[] 
		swap(x, y);  // ��ʱ y[] �Ѿ�û������, ���ǽ����������� x[] 
		p = 1, x[SA[0]] = 0;  // �ӵ�ǰ��С�ĺ�׺����ʼ, ��ÿ������һ��ֵ��ʾ����Դ�С 
		for(register int i = 1; i < n; i++) x[SA[i]] = (y[SA[i]] == y[SA[i - 1]] && y[SA[i] + k] == y[SA[i - 1] + k]) ? p - 1 : p++;  // ����ͬ�Ĵ�������ͬ��ֵ 
		if(p == n) break;  // �Ѿ��� n ����ͬ�ĺ�׺����, ˵�����д�����Դ�С�Ѿ���ȫȷ��, ����������� 
		m = p;  // �ַ��Ĳ�ͬȡֵֻ�� p ���� 
	}
	for(register int i = 1; i < n; i++) rnk[SA[i]] = i;  // rnk[i] ��ʾ�� i Ϊ��ͷ�ĺ�׺���ֵ�������, �� SA[] ���� 
	int k = 0, j;
	for(register int i = 0; i < n; ht[rnk[i++]] = k)
		for(k ? k-- : 0, j = SA[rnk[i] - 1]; s[i + k] == s[j + k]; k++);  // height ���������: height[rnk[i]] >= height[rnk[i - 1]] - 1 
	delete []x, delete []y, delete []cnt;
}

int main(){
	scanf("%s", s), n = strlen(s); 
	for(register int i = 0; i < n; i++) s[i] -= 'a' - 1;  // �� 'a' ~ 'z' ӳ�䵽 1 ~ 26 
	s[n++] = 0, buildSA(27);  // ���ַ��������һ����Сֵ 0, ��ֵ��Ϊ 0 ~ 26, �� 27 ��ֵ 
	for(register int i = 1; i < n; i++) printf("%d ", SA[i] + 1); puts("");  // �������ַ����� 0 ��ʼ���, ��Ϊ��Ŀ��Ҫ�� 1 ��ʼ���Լ� 1 
	for(register int i = 1; i < n; i++) printf("%d ", ht[i]); puts("");
	return 0;
}
