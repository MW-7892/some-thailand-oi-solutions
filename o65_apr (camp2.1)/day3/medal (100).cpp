#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;
vector<int> w;
vector<int> adj[100001];
long long dp[100001][11];
long long up[100001][21], du[100001][21][11], sm[100001];
int tin[100001], tout[100001], timer = 0;

void dfs(int a, int p){
	tin[a] = timer++;
	for(auto x : adj[a]){
		if(x == p) continue;
		sm[x] += (w[x] * 1ll) + sm[a];
		dfs(x, a);
		
		for(int i = 1; i <= 10; i++){
			dp[a][i] = max(dp[a][i], dp[x][i - 1] + (w[a] + w[x]) * 1ll);
		}
	}
	for(int i = 1; i <= 10; i++){
		for(int j = 1; j < i; j++){
			dp[a][i] = max(dp[a][i], dp[a][i - j] + dp[a][j]);
			if(i % j == 0) dp[a][i] = max(dp[a][i], dp[a][j] * ((i / j) * 1ll));
		}
	}
	tout[a] = timer++;
}

void dfs2(int a, int p){
	for(auto x : adj[a]){
		if(x == p) continue;
		for(int i = 1; i <= 10; i++){
			dp[x][i] = max(dp[x][i], dp[a][i - 1] + (w[x] + w[a]) * 1ll);
		}
		dfs2(x, a);
	}
	for(int i = 1; i <= 10; i++){
		for(int j = 1; j < i; j++){
			dp[a][i] = max(dp[a][i], dp[a][i - j] + dp[a][j]);
			if(i % j == 0) dp[a][i] = max(dp[a][i], dp[a][j] * ((i / j) * 1ll));
		}
	}
}

void proc_lca(int a, int p){
	up[a][0] = p;
	for(int k = 0; k <= 10; k++) du[a][0][k] = max(dp[a][k], dp[p][k]);
	
	for(int i = 1; i <= 20; i++){
		up[a][i] = up[up[a][i - 1]][i - 1];
		for(int k = 0; k <= 10; k++){
			du[a][i][k] = max(du[a][i - 1][k], du[up[a][i - 1]][i - 1][k]);
			for(int j = 0; j < k; j++){
				du[a][i][k] = max(du[a][i][k], du[a][i][k - j] + du[a][i][j]);
				if(j != 0 && k % j == 0) du[a][i][k] = max(du[a][i][k], du[a][i][j] * ((k / j) * 1ll));	
			}
		}
	}
	
	for(auto x : adj[a]) if(x != p) proc_lca(x, a);
}

bool is_pa(int u, int v){
	// u is ancestor of v
	if(tin[u] <= tin[v] && tout[v] <= tout[u]) return true;
	return false;
}

long long lca(int u, int v, int kk){
	if(is_pa(u, v)) return 0;
	
	int old_u = u, old_v = v;
	long long tmp[kk + 1];
	memset(tmp, 0, sizeof tmp);
	
	for(int i = 0; i <= kk; i++){
		tmp[i] = max(dp[u][i], dp[v][i]);
		for(int j = 0; j < i; j++){
			tmp[i] = max(tmp[i], dp[u][j] + dp[v][i - j]);
		}
	}
	for(int i = 20; i >= 0 && !is_pa(old_u, old_v); i--){
		if(!is_pa(up[u][i], old_v)){
			for(int j = 0; j <= kk; j++){
				tmp[j] = max(tmp[j], du[u][i][j]);
				for(int k = 0; k < j; k++){
					tmp[j] = max(tmp[j], tmp[k] + du[u][i][j - k]);
				}
			}
			u = up[u][i];
		}
	}
	
	for(int j = 0; j <= kk; j++){
		tmp[j] = max(tmp[j], du[u][0][j]);
		for(int k = 0; k < j; k++){
			tmp[j] = max(tmp[j], tmp[k] + du[u][0][j - k]);
		}
	}
		
	// printf(">> %d : %lld, %lld %lld\n", up[u][0], sm[up[u][0]], sm[old_u], sm[old_v]);
	
	return tmp[kk]
	+ (sm[old_u] + sm[old_v]) - ((2 * 1ll) * sm[up[u][0]]) + (w[up[u][0]] * 1ll);
	;
}

void initialize(int N, int Q, vector<int> W, vector<ii> R){
	w = W;
	for(auto x : R){
		adj[x.first].push_back(x.second);
		adj[x.second].push_back(x.first);
	}
	sm[0] = w[0] * 1ll;
	dfs(0, -1); 
	dfs2(0, -1);
	
	proc_lca(0, 0);
}

long long query(int A, int B, int X){
	X /= 2;
	if(A == B) return dp[A][X] + w[A];
	
	return max(lca(A, B, X), lca(B, A, X));
}
