#include <bits/stdc++.h>
using namespace std;
int h[100001], heavy[100001], pa[100001];
int head[100001], pos[100001];
int curpos = 0;

int tree[400004], lazy[400004];
vector<int> adj[100001];

int dsu[100001];

int findpa(int a){
	return dsu[a] == a ? a : dsu[a] = findpa(dsu[a]);
}

void push(int v){
	tree[v * 2] = max(tree[v * 2], lazy[v]);
	lazy[v * 2] = max(lazy[v * 2], lazy[v]);
	
	tree[v * 2 + 1] = max(tree[v * 2 + 1], lazy[v]);
	lazy[v * 2 + 1] = max(lazy[v * 2 + 1], lazy[v]);
	
	lazy[v] = 0;
}

void ins(int v, int tl, int tr, int l, int r, int val){
	if(l > r) return;
	if(tl == l && tr == r){
		tree[v] = max(tree[v], val);
		lazy[v] = max(lazy[v], val);
		return;
	}
	push(v);
	int tm = (tl + tr) >> 1;
	ins(v * 2, tl, tm, l, min(r, tm), val);
	ins(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, val);
	tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
}

int query(int v, int tl, int tr, int l, int r){
	if(l > r) return 0;
	if(tl == l && tr == r) return tree[v];
	push(v);
	int tm = (tl + tr) >> 1;
	return max(query(v * 2, tl, tm, l, min(r, tm)), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

// HLD

int dfs(int a, int p){
	int sz = 0, maxsz = 0;
	heavy[a] = -1;
	pa[a] = p;
	for(auto x : adj[a]){
		if(x == p) continue;
		h[x] = h[a] + 1;
		int kk = dfs(x, a);
		
		sz += kk;
		if(kk > maxsz){
			maxsz = kk;
			heavy[a] = x;
		}
	}
	return sz + 1;
}

void dec(int a, int p, int hh){
	pos[a] = ++curpos;
	head[a] = hh;
	if(heavy[a] != -1) dec(heavy[a], a, hh);
	
	for(auto x : adj[a]){
		if(x == p || x == heavy[a]) continue;
		dec(x, a, x);
	}
}

int query_HLD(int u, int v){
	int sum = 0;
	for(; head[u] != head[v]; u = pa[head[u]]){
		if(h[head[u]] < h[head[v]]) swap(u, v);
		// segment tree query pos[head[u]], pos[u]
		sum += query(1, 1, curpos, pos[head[u]], pos[u]);
	}
	if(h[u] < h[v]) swap(u, v);
	// segment tree query pos[v], pos[u]
	if(u != v) sum += query(1, 1, curpos, pos[v] + 1, pos[u]);
	return min(sum, 1);
}

int ins_HLD(int u, int v){
	// printf(">> %d %d\n", u, v);
	for(; head[u] != head[v]; u = pa[head[u]]){
		if(h[head[u]] < h[head[v]]) swap(u, v);
		// printf("!>> %d %d : %d %d --> %d %d\n", u, v, head[u], head[v], pos[head[u]], pos[u]);
		// segment tree query pos[head[u]], pos[u]
		ins(1, 1, curpos, pos[head[u]], pos[u], 1);
	}
	if(h[u] < h[v]) swap(u, v);
	// segment tree query pos[v], pos[u]
	if(u != v) ins(1, 1, curpos, pos[v] + 1, pos[u], 1);
}

void build_road(int u, int v){
	ins_HLD(u, v);
}

void initialize(int N, int M, int Q, vector<pair<int, int>> R){
	for(int i = 0; i <= N; i++) dsu[i] = i;
	queue<pair<int, int>> q;
	for(int i = 0; i < M; i++){
		int uu = R[i].first;
		int vv = R[i].second;
		
		if(findpa(uu) != findpa(vv)){
			adj[uu].push_back(vv);
			adj[vv].push_back(uu);
			
			dsu[findpa(uu)] = findpa(vv);
		}
		else q.push({uu, vv});
	}
	
	dfs(0, -1);
	dec(0, -1, 0);
	
	while(!q.empty()){
		int uu = q.front().first;
		int vv = q.front().second;
		q.pop();
		
		build_road(uu, vv);
	}
}

bool is_dangerous(int u, int v){
	int res = query_HLD(u, v);
	return res > 0 ? false : true;
}
