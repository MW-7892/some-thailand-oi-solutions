#include <bits/stdc++.h>
using namespace std;

pair<int, int> t[21][400004];
int pa[100001];
vector<int> adj[100001];
map<pair<int, int>, int> mp;
int mn = 100000, mx = 0;

void ins(int p, int v, int tl, int tr, int pos, int val){
	if(tl == pos && tr == tl){
		if(val > t[p][v].first) t[p][v] = make_pair(val, pos);
		return;
	}
	int tm = (tl + tr) >> 1;
	if(pos <= tm) ins(p, v * 2, tl, tm, pos, val);
	else ins(p, v * 2 + 1, tm + 1, tr, pos, val);
	
	if(t[p][v * 2].first > t[p][v * 2 + 1].first) t[p][v] = t[p][v * 2];
	else t[p][v] = t[p][v * 2 + 1];
}

pair<int, int> query(int p, int v, int tl, int tr, int l, int r){
	if(l > r) return make_pair(INT_MIN, -1);
	if(tl == l && tr == r) return t[p][v];
	int tm = (tl + tr) >> 1;
	
	pair<int, int> aa = query(p, v * 2, tl, tm, l, min(r, tm));
	pair<int, int> bb = query(p, v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
	
	if(aa.first > bb.first) return aa;
	else return bb;
}

void dfs(int a, int p, int rt, int dis){
	pa[a] = rt;
	mp[{rt, a}] = dis;
	for(auto x : adj[a]){
		if(x == p) continue;
		dfs(x, a, rt, dis + 1);
	}
}

void initialize(int N,int M,int S,std::vector<std::vector<int> >R)
{
	for(int i = 0; i < S; i++){
		mn = min(mn, R[i][0]);
		mx = max(mx, R[i][1]);
	}
	for(int i = S; i < M; i++){
		adj[R[i][0]].push_back(R[i][1]);
		adj[R[i][1]].push_back(R[i][0]);
	}
	for(int i = mn; i <= mx; i++) dfs(i, -1, i, 0);
	for(int i = 0; i <= 20; i++){
		for(int j = 0; j < 4 * N; j++){
			t[i][j] = make_pair(INT_MIN, -1);
		}
	}
}
void panda_spawn(int P,int L,int X)
{
	int dist = P - (L * mp[{pa[X], X}]);
	ins(0, 1, mn, mx, pa[X], dist);
	ins(L, 1, mn, mx, pa[X], dist - abs(pa[X] - mx)); // from left
	ins(L + 10, 1, mn, mx, pa[X], dist - abs(pa[X])); // from right
	return;
}

void panda_evac(int P,int L,int X)
{
	return;
}

int travel(int A,int B)
{
    pair<int, int> tmp = query(0, 1, mn, mx, A, B);
	if(tmp.first != INT_MIN) return tmp.first;
	else{
		for(int i = 1; i <= 10; i++){
			pair<int, int> tmp2 = query(i, 1, mn, mx, mn, A);
			tmp2.first -= (i * (A - tmp2.second));
			tmp.first = max(tmp.first, tmp2.first);
		}
		
		for(int i = 1; i <= 10; i++){
			pair<int, int> tmp2 = query(i, 1, mn, mx, B, mx);
			tmp2.first -= (i * (tmp2.second - B));
			tmp.first = max(tmp.first, tmp2.first);
		}
		return tmp.first;
	}
}
