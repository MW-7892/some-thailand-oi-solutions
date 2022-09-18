#include <bits/stdc++.h>
#include "findhome.h"
#define ii pair<int, int>
using namespace std;
int dist[301][301], tmpdist[301], cnt[301];
set<int> adj[301];
bool mark[301];

int find_home(int N, int M, vector<ii> R){
	for(auto x : R){
		adj[x.first].insert(x.second);
		adj[x.second].insert(x.first);
	}
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++) dist[i][j] = INT_MAX;
	}
	queue<int> q;
	for(int i = 0; i < N; i++){
		dist[i][i] = 0;
		q.push(i);
		while(!q.empty()){
			int n = q.front();
			q.pop();
			
			for(auto x : adj[n]){
				if(dist[i][x] > dist[i][n] + 1){
					dist[i][x] = dist[i][n] + 1;
					q.push(x);
				}
			}
		}
	}
	
	while(true){
		ii best = {1001, -1};
		for(int i = 0; i < N; i++){
			if(mark[i]) continue;
			// house to check
			int mx = 0; // max no. of house left from every case
			vector<int> shpa;
			for(int j = 0; j < N; j++){
				// check shortest path of all nodes
				if(mark[j]) continue;
				tmpdist[j] = INT_MAX;
				for(auto x : adj[i]){
					if(tmpdist[j] > dist[x][j]){
						tmpdist[j] = dist[x][j];
						shpa.clear();
						shpa.push_back(x);
					}
					else if(tmpdist[j] == dist[x][j]) shpa.push_back(x);
				}
				for(auto x : shpa){
					cnt[x]++;
				}
				shpa.clear();
			}
			for(auto x : adj[i]){
				mx = max(mx, cnt[x]);
				cnt[x] = 0;
			}
			if(mx < best.first) best = {mx, i};
			// printf(">> %d %d\n", i, mx);
		}
		// printf("== first check ==\n");
		int k = check(best.second);
		if(k == best.second) return k;
		
		mark[best.second] = true;
		for(int i = 0; i < N; i++){
			if(mark[i]) continue;
			for(auto x : adj[best.second]){
				if(dist[k][i] > dist[x][i]){
					mark[i] = true;
					break;
				}
			}
		}
	}
}
