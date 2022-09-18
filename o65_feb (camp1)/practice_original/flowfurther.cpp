#include <bits/stdc++.h>
using namespace std;
int dp[300001], dp2[50];
bitset<50> b[300001];
int in[300001], out[300001], rev[300001];
map<int, int> mp;
vector<int> adj[300001];
bitset<300001> vis;

vector<int> count_flow(int N, int E, int T, vector<int> u, vector<int> v){
	int cnt = 0;
	for(int i = 0; i < E; i++){
		in[v[i]]++;
		out[u[i]]++;
		
		adj[v[i]].push_back(u[i]);
	}
	
	queue<int> q;
	for(int i = 0; i < N; i++){
		if(in[i] > 1){
			mp[i] = cnt;
			rev[cnt++] = i;
		}
		if(out[i] == 0){
			q.push(i);
			vis[i] = 1;
		}
	}
	
	while(!q.empty()){
		int n = q.front();
		q.pop();
		
		//printf(">> %d\n", n);
		
		dp[n]++;
		if(mp.find(n) == mp.end()){
			for(auto x : adj[n]){
				b[x] |= b[n];
				dp[x] += dp[n];
				out[x]--;
				
				if(out[x] == 0 && !vis[x]){
					q.push(x);
					vis[x] = 1;
				}
			}
		}
		else{
			bitset<50> k = b[n];
			k[mp[n]] = 1;
			for(auto x : adj[n]){
				b[x] |= k;
				out[x]--;
				
				if(out[x] == 0 && !vis[x]){
					vis[x] = 1;
					q.push(x);
				}
			}
		}
	}

	

	vector<int> ans;
	for(int i = 0; i < N; i++){
		//printf("!! %d\n", i);
		if(mp.find(i) == mp.end()){
			for(int j = 0; j < T; j++){
				//if(b[i][j]) printf("\t>> %d\n", rev[j]);
				if(b[i][j]) dp[i] += dp[rev[j]];
			}
		}
	}
//	for(int i = 0; i < T; i++){
//		printf(">> %d %d\n", rev[i], dp2[i]);
//	}
	for(auto x : mp){
		for(int j = 0; j < T; j++){
			if(b[x.first][j]){
				dp2[x.second] += dp[rev[j]];
			}
		}
	}
	
	for(int i = 0; i < N; i++){
		if(mp.find(i) == mp.end()) ans.push_back(dp[i]);
		else ans.push_back(dp2[mp[i]] + dp[i]);
	}
	
	return ans;
}

/*
int main(){
	int N, E, T;
	vector<int> u, v;
	scanf("%d %d %d", &N, &E, &T);
	for(int i = 0, x, y; i < E; i++){
		scanf("%d %d", &x, &y);
		u.push_back(x);
		v.push_back(y);
	}
	vector<int> k = count_flow(N, E, T, u, v);
	for(auto x : k){
		printf("%d ", x);
	}
}
*/
