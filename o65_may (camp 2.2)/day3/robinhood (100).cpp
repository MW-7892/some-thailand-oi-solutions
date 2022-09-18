#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;
ii t[500001 << 2];
int N;
vector<int> A;

// Segtree for construction

ii max_pair(ii a, ii b){
	if(a.first > b.first || (a.first == b.first && a.second < b.second)) return a;
	return b;
}

void build(int v, int tl, int tr){
	if(tl == tr){
		t[v] = {A[tl], tl}; return;
	}
	int tm = (tl + tr) >> 1;
	build(v * 2, tl, tm); build(v * 2 + 1, tm + 1, tr);
	t[v] = max_pair(t[v * 2], t[v * 2 + 1]);
}

ii query(int v, int tl, int tr, int l, int r){
	if(l > r) return {INT_MIN, -1};
	if(tl == l && tr == r) return t[v];
	int tm = (tl + tr) >> 1;
	return max_pair(query(v * 2, tl, tm, l, min(r, tm)), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

// Cartesian tree

vector<ii> adj[500001];
void build_cartesian(int v, int l, int r){
	if(l >= r) return;
	ii left = query(1, 0, N - 1, l, v - 1); build_cartesian(left.second, l, v - 1);
	ii right = query(1, 0, N - 1, v + 1, r); build_cartesian(right.second, v + 1, r);
	
	if(left.second != -1){
		adj[v].push_back({left.second, A[v] - A[left.second]});
		adj[left.second].push_back({v, A[v] - A[left.second]});
	}
	if(right.second != -1){
		adj[v].push_back({right.second, A[v] - A[right.second]});
		adj[right.second].push_back({v, A[v] - A[right.second]});
	}
}

// Centroid

long long dist[21][500001];
int sz[500001], pa[500001], lvl[500001];
bool blocked[500001];
void dfs(int a, int p){
	sz[a] = 1;
	for(auto y : adj[a]){
		int x = y.first, w = y.second;
		if(x == p || blocked[x]) continue;
		dfs(x, a); sz[a] += sz[x];
	}
}

void dfs_dist(int a, int p, int lv){
	for(auto [x, w] : adj[a]){
		if(x == p || blocked[x]) continue;
		dist[lv][x] = dist[lv][a] + w;
		dfs_dist(x, a, lv);
	}
}

void dec(int v, int p){
	dfs(v, -1); int u = v, prev = 0;
	while(true){
		int mx = -1, nxt;
		for(auto y : adj[u]){
			int x = y.first, w = y.second;
			if(x == prev || blocked[x]) continue;
			if(sz[x] > mx){
				mx = sz[x]; nxt = x;
			}
		}
		if(mx * 2 > sz[v]){
			prev = u; u = nxt;
		}
		else break;
	}
	lvl[u] = p == -1 ? 0 : lvl[p] + 1;
	dfs_dist(u, u, lvl[u]);
	
	blocked[u] = true;
	pa[u] = p;
	
	for(auto y : adj[u]){
		int x = y.first, w = y.second;
		if(!blocked[x]) dec(x, u);
	}
}

// Insert & Query centroid

vector<long long> val(500001, 1e15);
int ask(int v){
	int old_v = v; long long ans = LLONG_MAX;
	while(v != -1){
		ans = min(ans, val[v] + dist[lvl[v]][old_v]);
		v = pa[v];
	} 
	return (ans + A[old_v]) >> 1;
}

void add(int v){
	int old_v = v;
	while(v != -1){
		val[v] = min(val[v], dist[lvl[v]][old_v]);
		v = pa[v];
	}
}

void initialize(vector<int> A_tmp, int M){
	A = A_tmp; N = A.size();
	build(1, 0, N - 1);

	ii rt = query(1, 0, N - 1, 0, N - 1);
	build_cartesian(rt.second, 0, N - 1);
	dec(rt.second, -1);
	
	add(0);
}
