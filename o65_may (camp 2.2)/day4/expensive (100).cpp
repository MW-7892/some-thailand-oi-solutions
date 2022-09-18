#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;
vector<ii> adj[1000001];
vector<ii> v1, v2;
ii pv;

struct cmp{
	bool operator() (const ii &a, const ii &b) const{
		int y1 = abs(pv.first - a.first), x1 = abs(pv.second - a.second);
		int y2 = abs(pv.first - b.first), x2 = abs(pv.second - b.second);
		
		return ((x2 * 1ll) * (y1 * 1ll)) < ((x1 * 1ll) * (y2 * 1ll));
	}
};

struct cmp2{
	bool operator() (const ii &a, const ii &b) const{
		return a.first > b.first || (a.first == b.first && a.second < b.second);
	}
};

vector<ii> dfs(int a, int p){
	if(adj[a].size() == 1) return {{0, 0}};
	
	vector<ii> tmp, ret;
	for(auto x : adj[a]){
		if(x.first == p) continue;
		vector<ii> k = dfs(x.first, a);
		
		for(auto y : k){
			int r = y.first, g = y.second;
			if(x.second == 1) r++;
			else g++;
			
			for(auto z : tmp){
				v1.push_back({r + z.first, g + z.second});
			}
		}
		for(auto y : k){
			int r = y.first, g = y.second;
			if(x.second == 1) r++;
			else g++;
			
			tmp.push_back({r, g});
		} 
	}
	return tmp;
}

void initialize(int N, int Q, vector<ii> R, vector<int> C){
	for(int i = 0; i < N - 1; i++){
		int u = R[i].first, v = R[i].second;
		int w = C[i];
		
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
	for(int i = 0; i < N; i++){
		if(adj[i].size() > 1){
			dfs(i, i);
			break;
		}
	}
	
	sort(v1.begin(), v1.end());
	

	deque<ii> dq;
	for(auto x : v1){
		int r = x.first, g = x.second;
		while(!dq.empty() && r >= dq.back().first && g >= dq.back().second) dq.pop_back();
		dq.push_back({r, g});
	}
	v1.clear();
	
	while(!dq.empty()){
		v1.push_back(dq.back());
		dq.pop_back();
	}

	pv = v1[0];
	sort(v1.begin() + 1, v1.end(), cmp());
}

long long most_expensive(int x, int y){
//	int l = 0, r = v1.size() - 1;
//	long long ret = ((x * 1ll) * (pv.first * 1ll)) + ((y * 1ll) * (pv.second * 1ll));
//	while(l < r){
//		int mid = (l + r) >> 1;
//		int x1 = abs(pv.first - v1[mid].first), y1 = abs(pv.second - v1[mid].second);
//		
//		bool cal = ((y * 1ll) * (x1 * 1ll)) > ((y1 * 1ll) * (x * 1ll));
//		ret = max(ret, ((x * 1ll) * (v1[mid].first * 1ll)) + ((y * 1ll) * (v1[mid].second * 1ll)));
//		
//		if(cal) l = mid + 1;
//		else r = mid;
//	}
	long long ret = 0;
	for(auto xx : v1){
		ret = max(ret, ((xx.first * 1ll) * (x * 1ll)) + ((xx.second * 1ll) * (y * 1ll)));
	}
	return ret;
}
