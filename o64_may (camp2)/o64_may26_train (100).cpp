#include <bits/stdc++.h>
#include "train.h"
#define ii pair<int, int>
using namespace std;
vector<array<int, 3>> a;
vector<int> tree(800008, INT_MAX), lazy(800008, INT_MAX);

void push(int v){
	if(lazy[v] == INT_MAX) return;
	lazy[v * 2] = min(lazy[v * 2], lazy[v]);
	tree[v * 2] = min(tree[v * 2], lazy[v]);
	
	lazy[v * 2 + 1] = min(lazy[v * 2 + 1], lazy[v]);
	tree[v * 2 + 1] = min(tree[v * 2 + 1], lazy[v]);
	
	lazy[v] = INT_MAX;
}

void ins(int v, int tl, int tr, int l, int r, int val){
	if(l > r) return;
	if(l == tl && r == tr){
		tree[v] = min(tree[v], val);
		lazy[v] = min(lazy[v], val);
		return;
	}
	push(v);
	int tm = (tl + tr) >> 1;
	ins(v * 2, tl, tm, l, min(r, tm), val);
	ins(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, val);
	tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}

int query(int v, int tl, int tr, int l, int r){
	if(l > r || tree[v] == INT_MAX) return INT_MAX;
	if(l == tl && r == tr) return tree[v];
	push(v);
	int tm = (tl + tr) >> 1;
	return min(query(v * 2, tl, tm, l, min(r, tm)), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

int find_min_cost(int N, int M, vector<int> &s, vector<int> &t, vector<int> &c){
	ins(1, 1, N, 1, 1, 0);
	for(int i = 0; i < M; i++){
		int q = query(1, 1, N, s[i] + 1, t[i] + 1);
		if(q != INT_MAX) ins(1, 1, N, s[i] + 1, t[i] + 1, q + c[i]);
	}
	int ans = query(1, 1, N, N, N);
	return (ans == INT_MAX ? -1 : ans);
}
