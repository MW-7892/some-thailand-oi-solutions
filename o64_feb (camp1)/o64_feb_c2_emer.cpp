#include <bits/stdc++.h>
#include "emergency.h"
#define ii pair<int, int>
#define pi pair<ii, ii>
using namespace std;
vector<ii> adj[200001];
int tt[200001];
pi h[200001], c[200001];
int ans = 0;

pi dfs(int a, int p, int s){
	priority_queue<ii> pq;
	if(tt[a] == s) pq.push(make_pair(0, a));
	for(auto x : adj[a]){
		if(x.first == p) continue;
		pi tmp = dfs(x.first, a, s);
		
		if(tmp.first.first != -1) pq.push(make_pair(tmp.first.first + x.second, x.first));
		if(tmp.second.first != -1) pq.push(make_pair(tmp.second.first + x.second, x.first));
	}
	ii k[2] = {make_pair(-1, -1), make_pair(-1, -1)};
	int kk = -1, idx = 0;
	while(!pq.empty()){
		if(pq.top().second == kk){
			pq.pop();
			continue;
		}
		k[idx++] = pq.top();
		kk = pq.top().second;
		if(idx == 2) break;
	}
	while(!pq.empty()) pq.pop();
	if(s == 1) return h[a] = make_pair(k[0], k[1]);
	return c[a] = make_pair(k[0], k[1]);
}

void solve(int a, int p, int mxc){
	// printf(">> %d %d %d\n", a, p, mxc);
	if(tt[a] == 2) mxc = max(mxc, 0);
	if(tt[a] == 1) ans = max({ans, mxc, c[a].first.first});
	for(auto x : adj[a]){
		if(x.first == p) continue;
		if(c[a].first.second == x.first){
			int tmp = -1;
			if(c[a].second.first != -1) tmp = max(tmp, c[a].second.first + x.second);
			if(mxc != -1) tmp = max(tmp, mxc + x.second);
			solve(x.first, a, tmp);
		}
		else{
			int tmp = -1;
			if(c[a].first.first != -1) tmp = max(tmp, c[a].first.first + x.second);
			if(mxc != -1) tmp = max(tmp, mxc + x.second);
			solve(x.first, a, tmp);
		}
	}
}

int furthest(int N, int H, int K, int roads[][2], int lengths[], int hospitals[], int centers[]){
	for(int i = 0; i < N - 1; i++){
		adj[roads[i][0]].push_back(make_pair(roads[i][1], lengths[i]));
		adj[roads[i][1]].push_back(make_pair(roads[i][0], lengths[i]));	
	}
	for(int i = 0; i < H; i++) tt[hospitals[i]] = 1;
	for(int i = 0; i < K; i++) tt[centers[i]] = 2;
	
	dfs(0, -1, 1);
	dfs(0, -1, 2);
	
	/*
	for(int i = 0; i < N; i++){
		printf("\nnode %d:\n", i);
		printf("  top H = (%d, %d)\n", h[i].first.first, h[i].first.second);
		printf("  second H = (%d, %d)\n\n", h[i].second.first, h[i].second.second);
		
		printf("  top C = (%d, %d)\n", c[i].first.first, c[i].first.second);
		printf("  second C = (%d, %d)\n", c[i].second.first, c[i].second.second);
	}
	*/
	
	solve(0, -1, -1);
	return ans;
}

/*
int main(){
	
	int a = 5, b = 1, c = 1;
	int d[4][2] = {{0, 1}, {0, 2}, {3, 2}, {1, 4}};
	int e[4] = {4, 7, 10, 5};
	int f[1] = {4};
	int g[1] = {3};
	printf("%d", furthest(a, b, c, d, e, f, g));
	
}
*/
