#include <bits/stdc++.h>
#include "inversion.h"
using namespace std;
int tree[400004 << 2];
int a[200001];
const int offset = 200001;
// use 0 as pivot

void ins(int v, int tl, int tr, int pos, int val = 1){
	if(tl == tr){
		tree[v] = val;
		return;
	}
	int tm = (tl + tr) >> 1;
	if(pos <= tm) ins(v * 2, tl, tm, pos, val);
	else ins(v * 2 + 1, tm + 1, tr, pos, val);
	tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

int query(int v, int tl, int tr, int l, int r){
	if(l > r) return 0;
	if(tl == l && tr == r) return tree[v];
	int tm = (tl + tr) >> 1;
	return query(v * 2, tl, tm, l, min(r, tm)) + query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

int find_pos(int di, int st, int k, int N){
	int l, r;
	if(di == 0){
		// left
		l = 0, r = st + offset;
		while(l < r){
			int mid = (l + r) >> 1;
			// printf(">> %d %d %d\n", l, r, mid);
			int qq = query(1, 1, N + offset, mid + 1, st + offset);
			// printf("qq = %d\n", qq);
			if((st + offset) - (mid + 1) + 1 - qq >= k) l = mid + 1;
			else r = mid;
		}
		return l - offset;
	}
	else{
		l = st + offset, r = N + offset;
		while(l < r){
			int mid = (l + r) >> 1;
			int qq = query(1, 1, N + offset, st + offset, mid);
			// printf(">> %d %d %d\n", l - offset, r - offset, mid - offset);
			// printf("qq = %d\n", mid - (st + offset) + 1 - qq);
			if(mid - (st + offset) + 1 - qq >= k) r = mid;
			else l = mid + 1;
		}
		return l - offset;
	}
}

vector<int> find_permutation(int N, long long V){
	int old = 0, mn = 0;
	ins(1, 1, N + offset, offset);
	for(int i = N - 1; i > 0; i--){
		long long K = swap_and_report(0, i);
		long long diff = max(K, V) - min(K, V);
		long long in_range = (diff - 1ll) >> 1;
		// current 0 pos is i
		int now;
		
		if(K < V){
			// true value a[0] > a[i]
			// printf("ok");
			now = find_pos(0, old, int(in_range) + 1, N);
			ins(1, 1, N + offset, now + offset);
			
			a[i] = now;
		}
		else{
			// true value a[0] < a[i]
			now = find_pos(1, old, int(in_range) + 1, N);
			ins(1, 1, N + offset, now + offset);
			
			a[i] = now;
		}
		
		// printf("!!! >>> %lld %d %d\n", in_range, old, now);
		
		mn = min(mn, a[i]);
		old = now;
		V = K;
	}
	vector<int> ans;
	for(int i = 0; i < N; i++) ans.push_back(a[i] - mn + 1);
	return ans;
}
