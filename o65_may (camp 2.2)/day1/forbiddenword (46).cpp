#include <bits/stdc++.h>
#include "forbiddenwords.h"
#define ii pair<int, int>
using namespace std;
vector<int> adj[101], adj2[101];
bool chk[101], adjf[101][101];
int N, M, lg;
long long X;

bool build(int a, int idx){
	if(idx >= 60) return true;
	bool ok1 = false;
	for(int i = 0; i < M; i++){
		if(chk[i] || adjf[i][a]) continue;
		
		chk[i] = true;
		bool q = build(i, idx + 1);
		chk[i] = false;
		
		if(q){
			ok1 = true;
			adj[a].push_back(i);
			chk[i] = true;
			break;
		}
	}
	bool ok2 = true;
	if(X & (1ll << idx)){
		ok2 = false;
		for(int i = 0; i < M; i++){
			if(chk[i] || adjf[i][a]) continue;
			ok2 = true; chk[i] = true;
			adj[a].push_back(i);
			break;
		}
	}
	return ok1 && ok2;
}

long long ans = 0;
void dfs(int a, int p, int idx){
	if(idx >= 60) return;
	if(adj2[a].size() == 1){
		ans += (1ll << (idx - 1));
		return;
	}
	for(auto x : adj2[a]){
		if(x == p) continue;
		dfs(x, a, idx + 1);
	}
}

vector<ii> alice(int m, int n, int K, long long xx, vector<ii> F){
	N = n; M = m; X = xx;
	
	for(auto x : F){
		adjf[x.first][x.second] = adjf[x.second][x.first] = true;
	}
	// for(int i = 0; i < M - 1; i++) adjf[0][i + 1] = true;
	for(int i = M - 1; i >= 0; i--){
		int cnt = 0; chk[i] = true;
		for(int j = 0; j < M; j++){
			if(chk[j] || adjf[i][j]) continue;
			if(cnt == 0){
				chk[j] = true;
				bool q = build(j, 0);
				chk[j] = false;
				
				if(!q){
					for(int k = 0; k < M; k++) adj[k].clear();
					memset(chk, 0, sizeof chk);
					continue;
				}
				else{
					chk[j] = true;
					adj[i].push_back(j);
					cnt++;
				}
			}
			else{
				adj[i].push_back(j);
				chk[j] = true;
				cnt++;
			}
			if(cnt >= 4) break;
		}
		if(cnt < 4) chk[i] = false;
		else break;
	}
	vector<ii> ret;
	for(int i = 0; i < M; i++){
		for(auto x : adj[i]) ret.push_back({i, x});
		adj[i].clear();
	}
	memset(chk, 0, sizeof chk);
	memset(adjf, 0, sizeof adjf);
	// for(auto x : ret) printf(">> %d %d\n", x.first, x.second);
	return ret;
}



long long bob(int M, vector<ii> W){
	ans = 0;
	for(auto x : W){
		adj2[x.first].push_back(x.second);
		adj2[x.second].push_back(x.first);
	}
	for(int i = 0; i < M; i++){
		if(adj2[i].size() >= 4){
			for(auto x : adj2[i]){
				if(adj2[x].size() > 1){
					dfs(x, i, 0);
				}
			}
		}
	}
	for(int i = 0; i < M; i++) adj2[i].clear();
	return ans;
}
