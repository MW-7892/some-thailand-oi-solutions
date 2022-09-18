#include <bits/stdc++.h>
// #include "colorful.h"
#define ii pair<int, int>
using namespace std;
unordered_map<int, long long> vis, vis2;
set<int> adj[50001];
int to[50001][401];
vector<int> prime;
int md, NN;

int hasher(int s, int c){
	return s * 50000 + c;
}

void init_machine(int N, int M, int K, int Q, vector<int> X, vector<int> Y){
	md = K; NN = N;
	for(int i = 0; i < M; i++){
		adj[X[i]].insert(Y[i]);
		adj[Y[i]].insert(X[i]);
	}
	prime.push_back(2);
	for(int i = 3; prime.size() <= K + 5; i += 2){
		bool no = false;
		for(auto x : prime){
			if(x * x > i) break;
			if(i % x == 0){
				no = true;
				break;
			}
		}
		if(!no) prime.push_back(i);
	}
}

int send_ball(int c, int s, long long t){
	vis[hasher(s, c)] = t;
	while(t > 0){
		if(to[s][c] == 0){
			pair<int, int> best = {INT_MAX, s};
			for(auto x : adj[s]){
				if((x % prime[c]) < best.first) best = {x % prime[c], x};
				if(best.first == 0) break;
			}
			to[s][c] = best.second;	
		}
		if(to[s][c] == s){
			return s;
		}
		s = to[s][c]; c = (c + 1) % md; t--;
		
		if(vis2[hasher(s, c)]){
			t %= vis2[hasher(s, c)];
			while(t > 0){
				s = to[s][c]; c = (c + 1) % md; t--;
			}
			return s;
		}
		
		if(vis.find(hasher(s, c)) == vis.end()) vis[hasher(s, c)] = t;
		else{
			t %= abs(t - vis[hasher(s, c)]);
			vis2[hasher(s, c)] = abs(t - vis[hasher(s, c)]);
			while(t > 0){
				s = to[s][c]; c = (c + 1) % md; t--;
			}
			break;
		}
	}
	return s;
}
