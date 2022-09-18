#include <bits/stdc++.h>
#include "rumors.h"
#define ii pair<int, int>
using namespace std;
priority_queue<ii, vector<ii>, greater<ii> > pq;
int dp[2002][2002];

vector<int> analyze_rumors(int N, int K, int Q, vector<int> D, vector<int> X, vector<int> J){
	for(int i = 0; i < N; i++) dp[i][1] = 0;
	for(int i = 2; i <= N; i++){
		int sm = 0;
		for(int j = 1; j < i; j++) sm += (D[j] - D[j - 1] - 1) / K;
		pq.push({sm, 0});
		for(int j = 0; j < N; j++){
			while(!pq.empty() && pq.top().second <= j - i) pq.pop();
			dp[j][i] = pq.top().first;
			
			if(j + i < N){
				sm += (D[j + i] - D[j + i - 1] - 1) / K;
				sm -= (D[j + 1] - D[j] - 1) / K;
				pq.push({sm, j + 1});
			}
		}
		while(!pq.empty()) pq.pop();
	}
	vector<int> ans;
	for(int i = 0; i < Q; i++){
		int l = 1, r = N;
		while(l < r){
			int mid = (l + r + 1) >> 1;
			if(dp[X[i]][mid] > J[i]) r = mid - 1;
			else l = mid;
		}
		ans.push_back(l);
	}
	return ans;
}

