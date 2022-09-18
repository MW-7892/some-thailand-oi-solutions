#include <bits/stdc++.h>
using namespace std;
int qs[200002];
int fwt[200002], cnt[200002];
long long ans = 0;
bool chk = true;

void ins(int v, int val){
	for(; v > 0; v -= (v & -v)) fwt[v] += val;
}

int query(int v){
	int ret = 0;
	for(; v <= 200000 ; v += (v & -v)) ret += fwt[v];
	return ret;
}

void init_monkeys(vector<int> P, int Q){
  int N = P.size();
  for(int i = 0; i < N; i++){
  	P[i]++;
  	cnt[P[i]]++;
  	if(cnt[P[i]] > 1) chk = false;
  	ans += query(P[i]) * 1ll;
  	ins(P[i], 1);
  }
}

long long minimum_branches(int L, int R){
  return chk ? ans : -1;
}
