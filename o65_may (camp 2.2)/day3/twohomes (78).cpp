#include <bits/stdc++.h>
#include "twohomes.h"
#define ii pair<int, int>
using namespace std;
vector<int> dep[1001], adj2[1001];
vector<ii> ed[1001];
int pa[1001], h[1001], maxh = 0;
map<ii, int> mp;
bool blocked[1001];

void dfs(int a, int p, int dd){
	pa[a] = p; h[a] = dd; dep[dd].push_back(a);
	maxh = max(maxh, dd);
	for(auto x : adj2[a]){
		if(blocked[x] || x == p) continue;
		dfs(x, a, dd + 1);
		ed[dd + 1].push_back({a, x});
	}
}

ii find_homes(int N, int M, vector<vector<int>> R){
	// bool is_reachable(vector<int> C);
	for(int i = 0; i < M; i++){
		vector<int> x = R[i];
		adj2[x[0]].push_back(x[1]);
		adj2[x[1]].push_back(x[0]);
		
		mp[{x[0], x[1]}] = mp[{x[1], x[0]}] = i;
	}
	dfs(0, 0, 0);
	int l = 0, r = maxh + 1;
	while(l < r){
		int mid = (l + r + 1) >> 1;
		vector<int> ask;
		for(int i = 0; i < mid; i++){
			for(auto x : ed[i]) ask.push_back(mp[x]);
		}
		bool q = is_reachable(ask);
		
		if(q) l = mid;
		else r = mid - 1;
	}
	// all lca candidates
	vector<int> lca_c;
	for(auto x : ed[l]) lca_c.push_back(x.first);
	l = 0, r = lca_c.size();
	while(l < r){
		int mid = (l + r + 1) >> 1;
		vector<int> ask2;
		for(int i = 0; i < mid; i++){
			for(auto x : adj2[lca_c[i]]) ask2.push_back(mp[{lca_c[i], x}]);
		}
		bool q = is_reachable(ask2);
		if(q) l = mid;
		else r = mid - 1;
	}
	// got lca, b-search for lower start
	int lca = lca_c[l];
	l = h[lca], r = maxh;
	while(l < r){
		int mid = (l + r + 1) >> 1;
		vector<int> ask3;
		for(auto x : dep[mid]) ask3.push_back(mp[{pa[x], x}]);
		
		bool q = is_reachable(ask3);
		if(q) r = mid - 1;
		else l = mid;
	}

	// candidates for start
	vector<int> st_c;
	for(auto x : dep[l]) st_c.push_back(x);

	l = 0, r = st_c.size();
	while(l < r){
		if(st_c.size() == 1){
			l = r = 0; break;
		}
		int mid = (l + r + 1) >> 1;
		vector<int> ask4;
		for(int i = 0; i < mid; i++) ask4.push_back(mp[{pa[st_c[i]], st_c[i]}]);
		bool q = is_reachable(ask4);
		if(q) l = mid;
		else{
			r = mid - 1;
		}
	}
	
	int st = st_c[l];
	// found start, ignore start tree
	for(int i = st; i != lca; i = pa[i]) blocked[i] = true;
	for(int i = 0; i <= maxh; i++){
		ed[i].clear(); dep[i].clear();
	}

	dfs(lca, pa[lca], h[lca]);
	
	l = h[lca], r = maxh;
	while(l < r){
		int mid = (l + r + 1) >> 1;
		vector<int> ask3;
		for(auto x : dep[mid]) ask3.push_back(mp[{pa[x], x}]);
		
		bool q = is_reachable(ask3);
		if(q) r = mid - 1;
		else l = mid;
	}
	// candidates for start
	vector<int> ed_c;
	for(auto x : dep[l]) ed_c.push_back(x);
	l = 0, r = ed_c.size();
	while(l < r){
		if(ed_c.size() == 1){
			l = r = 0; break;
		}
		int mid = (l + r + 1) >> 1;
		vector<int> ask4;
		for(int i = 0; i < mid; i++) ask4.push_back(mp[{pa[ed_c[i]], ed_c[i]}]);
		bool q = is_reachable(ask4);
		if(q) l = mid;
		else{
			r = mid - 1;
		}
	}
	int ee = ed_c[l];
	return {st, ee};
}
