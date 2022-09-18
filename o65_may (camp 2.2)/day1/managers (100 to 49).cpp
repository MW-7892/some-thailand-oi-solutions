#include <bits/stdc++.h>
using namespace std;
int N, Q, len, lg;
// X < sqrt(N), some kind of lca
// X >= sqrt(N), persisten seg tree

int up[350][50001][20];
map<int, int> mp;
int chk[50001];

struct node{
	int val;
	node *l, *r;
	
	node(int a): l(nullptr), r(nullptr), val(a) {}
	node(node* ll, node* rr){
		l = ll; r = rr; val = 0;
		if(l) val += l->val;
		if(r) val += r->val;
	}
};

node* root[50001];

// 1 - index
node* build(int tl = 0, int tr = N - 1){
	if(tl == tr) return new node(0);
	int tm = (tl + tr) >> 1;
	return new node(build(tl, tm), build(tm + 1, tr));
}

node* ins(node* v, int tl, int tr, int pos, int val){
	if(tl == tr) return new node(v->val + val);
	int tm = (tl + tr) >> 1;
	if(pos <= tm) return new node(ins(v->l, tl, tm, pos, val), v->r);
	else return new node(v->l, ins(v->r, tm + 1, tr, pos, val));
}

int query(node* v, int tl, int tr, int l, int r){
	if(l > r) return 0;
	if(tl == l && r == tr) return v->val;
	int tm = (tl + tr) >> 1;
	
	return query(v->l, tl, tm, l, min(r, tm)) + query(v->r, tm + 1, tr, max(l, tm + 1), r);
}

void initialize(int n, int q, vector<int> A){
	N = n; Q = q;
	len = min(int(ceil(sqrt(N))) + 100, N);
	lg = int(ceil(log2(N)));
	
	int cnt = 1;
	for(int i = 0; i < N; i++){
		if(mp.find(A[i]) == mp.end()) mp[A[i]] = cnt++;
		A[i] = mp[A[i]];
	}

	
	for(int i = 1; i < len; i++){
		int head = N - 1; cnt = 0;
		for(int j = N - 1; j >= 0; j--){
			if(!chk[A[j]]) cnt++;
			chk[A[j]]++;
			
			while(cnt > i){
				chk[A[head]]--;
				if(!chk[A[head]]) cnt--;
				head--;
			}
			
			up[i][j][0] = head;
			for(int k = 1; k <= lg; k++){
				up[i][j][k] = up[i][min(up[i][j][k - 1] + 1, N - 1)][k - 1];
				if(up[i][j][k] == 0) up[i][j][k] = N - 1;
			}
		}
		while(head >= 0){
			chk[A[head]]--;
			head--;
		}
	}

	mp.clear();
	root[0] = build();

	for(int i = 0; i < N; i++){
		root[i + 1] = ins(root[i], 0, N - 1, i, 1);
		if(mp.find(A[i]) != mp.end()){
			root[i + 1] = ins(root[i + 1], 0, N - 1, mp[A[i]], -1);
		}
		mp[A[i]] = i;
	}
}

int min_managers(int L, int R, int X){
	if(X < len){
		int ret = 0;
		for(int i = lg; i >= 0; i--){
			// printf(">> %d %d %d\n", L, i, up[X][L][i]);
			if(up[X][L][i] < R){
				L = up[X][L][i] + 1;
				ret += (1 << i);
			}
		}
		return ret + 1;
	}
	else{
		int head = L - 1;
		int ret = 0;
		while(head < R){
			int l = head + 1, r = R;
			while(l < r){
				int mid = (l + r + 1) >> 1;
				int q = query(root[mid + 1], 0, N - 1, head + 1, R);
				if(q <= X) l = mid;
				else r = mid - 1;
			}
			head = l;
			ret++;
		}
		return ret;
	}
}
