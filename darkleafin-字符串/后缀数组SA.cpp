// 后缀数组 (Suffix Array, SA) (2018.2.23)
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
	for(register int i = 0; i < m; i++) cnt[i] = 0;  // 清空桶, 进行基数排序 
	for(register int i = 0; i < n; i++) cnt[x[i] = s[i]]++;  // x[] 为第 i 位字符的相对大小 
	for(register int i = 1; i < m; i++) cnt[i] += cnt[i - 1];  // 找到每个值排序后的开始位置 
	for(register int i = n - 1; i >= 0; i--) SA[--cnt[x[i]]] = i;   // 将每个后缀按第一位稳定排序的结果存入 SA[] 
	for(register int k = 1; k <= n; k <<= 1){  // 倍增两个关键字之间的距离 k 
		int p = 0;
		for(register int i = n - k; i < n; i++) y[p++] = i;  // 将末尾第二关键字超出范围 n 的看作 0, 因为 0 最小所以放在最前面 
		for(register int i = 0; i < n; i++) if(SA[i] >= k) y[p++] = SA[i] - k;  // SA 为当前第二关键字排好序的位置, 减去 k 即得对应的第一关键字, 这样存 y[] 对应的串就按第二关键字排好序了 
		for(register int i = 0; i < m; i++) cnt[i] = 0;  // 进行基数排序 
		for(register int i = 0; i < n; i++) cnt[x[y[i]]]++;  // 原来的 i 用 y[i] 代替, 保证第二关键字稳定 
		for(register int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
		for(register int i = n - 1; i >= 0; i--) SA[--cnt[x[y[i]]]] = y[i];  // 更新 SA[] 
		swap(x, y);  // 此时 y[] 已经没有用了, 我们借助它来更新 x[] 
		p = 1, x[SA[0]] = 0;  // 从当前最小的后缀串开始, 给每个串赋一个值表示其相对大小 
		for(register int i = 1; i < n; i++) x[SA[i]] = (y[SA[i]] == y[SA[i - 1]] && y[SA[i] + k] == y[SA[i - 1] + k]) ? p - 1 : p++;  // 将相同的串赋上相同的值 
		if(p == n) break;  // 已经有 n 个不同的后缀串了, 说明所有串的相对大小已经完全确定, 无需继续倍增 
		m = p;  // 字符的不同取值只有 p 个了 
	}
	for(register int i = 1; i < n; i++) rnk[SA[i]] = i;  // rnk[i] 表示以 i 为开头的后缀的字典序排名, 与 SA[] 互逆 
	int k = 0, j;
	for(register int i = 0; i < n; ht[rnk[i++]] = k)
		for(k ? k-- : 0, j = SA[rnk[i] - 1]; s[i + k] == s[j + k]; k++);  // height 数组的性质: height[rnk[i]] >= height[rnk[i - 1]] - 1 
	delete []x, delete []y, delete []cnt;
}

int main(){
	scanf("%s", s), n = strlen(s); 
	for(register int i = 0; i < n; i++) s[i] -= 'a' - 1;  // 将 'a' ~ 'z' 映射到 1 ~ 26 
	s[n++] = 0, buildSA(27);  // 在字符串后面加一个最小值 0, 总值域为 0 ~ 26, 共 27 个值 
	for(register int i = 1; i < n; i++) printf("%d ", SA[i] + 1); puts("");  // 本程序字符串从 0 开始编号, 因为题目需要从 1 开始所以加 1 
	for(register int i = 1; i < n; i++) printf("%d ", ht[i]); puts("");
	return 0;
}
