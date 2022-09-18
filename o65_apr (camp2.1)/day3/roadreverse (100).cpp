#include <bits/stdc++.h>
#define ii pair<int, int>
#define pi pair<int, ii>
using namespace std;
int dp[100001][11];
bool vis[100001];
ii pos[100001];
vector<int> adj[100001];

void dfs(int a){
	if(vis[a]) return;
	vis[a] = true;
	for(auto x : adj[a]){
		int hx = pos[x].first, px = pos[x].second;
		dp[a][hx] = min(dp[a][hx], px);
		
		dfs(x);
		if(x == 0){
			for(int i = 1; i <= 10; i++) dp[a][i] = 0;
		}
		
		for(int i = 1; i <= 10; i++){
			dp[a][i] = min(dp[x][i], dp[a][i]);
		}
	}
}

int count_roads(int N, int M, int K, vector<vector<int>> S, vector<pair<int, int>> R){
	for(int i = 0; i < N; i++){
		for(int j = 0; j <= 10; j++) dp[i][j] = INT_MAX;
	}
	
	for(auto x : R) adj[x.first].push_back(x.second);
	
	for(int i = 0; i < K; i++){
		R.push_back({0, S[i][0]});
		adj[0].push_back(S[i][0]);
		for(int j = 0; j < S[i].size(); j++){
			pos[S[i][j]] = {i + 1, j};
			if(j < S[i].size() - 1){
				adj[S[i][j]].push_back(S[i][j + 1]);
				R.push_back({S[i][j], S[i][j + 1]});
			}
		}
	}
	
	dfs(0);
	int ans = 0;
	for(auto x : R){
		int u = x.first, v = x.second;
		int hv = pos[v].first, pv = pos[v].second;
		
		for(auto y : adj[u]){
			if(y == v) continue;
			if((pos[y].first == hv && pos[y].second <= pv) || dp[y][hv] <= pv){
				ans++;
				break;
			}
		}
	}
	return M - ans;
}
