#include <bits/stdc++.h>
using namespace std;
// observe: 2 --> 3 (+2), 3 --> 4 (+4), 4 --> 5 (+2?)
long long icnt[200001], side[200001], slen[200001], node[200001];
long long md = 1e9 + 7;
long long fwt[2][200001];

void ins(int p, int v, int a){
	v++;
	for(; v <= 200000; v += (v & -v)) fwt[p][v] += a * 1ll;
}

long long query(int p, int v){
	v++;
	long long ret = 0;
	for(; v > 0; v -= (v & -v)) ret += fwt[p][v];
	return ret;
}

int minimum_cost(int N, vector<int> w){
	icnt[0] = 4; side[0] = 3;
	for(int i = 1; i < N; i++){
		if(i % 2) icnt[i] = ((icnt[i - 1] * (4 * 1ll)) + (2 * 1ll)) % md;
		else icnt[i] = ((icnt[i - 1] * (4 * 1ll)) + (4 * 1ll)) % md;
		
		side[i] = ((side[i - 1] * (4 * 1ll)) + (3 * 1ll)) % md;
	}
	slen[N - 1] = 2;
	for(int i = N - 2; i >= 0; i--) slen[i] = (slen[i + 1] * (2 * 1ll)) % md;
	for(int i = 0; i < N; i++) node[i] = ((side[i] * slen[i]) + 1ll) % md;
	
	vector<pair<int, int> > v;
	for(int i = 0; i < N; i++) v.push_back({w[i], i});
	sort(v.begin(), v.end());
	
	long long ans = ((node[v[0].second] - 1ll) * v[0].first) % md;
	ins(0, v[0].second, 1); ins(1, v[0].second, icnt[v[0].second]);
	for(int i = 1; i < N; i++){
		// printf("!! %d : %lld\n", v[i].second, node[v[i].second] - (icnt[v[i].second] * i));
		long long tmp = node[v[i].second];
		tmp -= query(1, v[i].second); tmp %= md;
		tmp -= ((i * 1ll) - query(0, v[i].second)) * icnt[v[i].second]; tmp %= md;
		if(tmp < 0) tmp += md;
		
		ans += (max(0 * 1ll, tmp) * v[i].first) % md;
		ans %= md;
		if(ans < 0) ans += md;
		
		ins(0, v[i].second, 1);
		ins(1, v[i].second, icnt[v[i].second]);
	}
	return int(ans);
} 

/*
int main(){
  int N;
  scanf("%d",&N);
  std::vector<int> w;
  w.reserve(N);
  for(int i = 0; i < N; i++){
    int x;
    scanf("%d",&x);
    w.push_back(x);
  }
  printf("%d\n", minimum_cost(N, w));
  return 0;
}
*/
