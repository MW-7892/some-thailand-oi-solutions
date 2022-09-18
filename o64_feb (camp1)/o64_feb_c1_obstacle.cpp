#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > dp, dist, rev;
int NN, MM;

void initialize(int N, int M, int Q, vector<vector<int> > & rowlen, vector<vector<int> > & collen){
	NN = N; MM = M;
	for(int i = 0; i < N; i++){
		vector<int> tmp(M, INT_MAX);
		dp.push_back(tmp);
		dist.push_back(tmp);
		rev.push_back(tmp);
	}
	dist[0][0] = 0;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			if(i > 0) dist[i][j] = min(dist[i][j], dist[i - 1][j] + collen[i - 1][j]);
			if(j > 0) dist[i][j] = min(dist[i][j], dist[i][j - 1] + rowlen[i][j - 1]);
		}
	}
	
	rev[N - 1][M - 1] = 0;
	for(int i = N - 1; i >= 0; i--){
		for(int j = M - 1; j >= 0; j--){
			if(i < N - 1) rev[i][j] = min(rev[i][j], rev[i + 1][j] + collen[i][j]);
			if(j < M - 1) rev[i][j] = min(rev[i][j], rev[i][j + 1] + rowlen[i][j]);
		}
	}
	
	for(int i = N - 1; i >= 0; i--){
		for(int j = 0; j < M - 1; j++){
			if(i == N - 1) dp[i][j] = dist[i][j] + rev[i][j + 1] + rowlen[i][j];
			else dp[i][j] = min(dp[i + 1][j], dist[i][j] + rev[i][j + 1] + rowlen[i][j]);
		}
	}
}

int ask(int r, int c){
	if(c == 0 || r == NN - 1) return -1;
	return dp[r + 1][c - 1];
}

/*
int main(){
	int N, M, Q;
	scanf("%d %d %d", &N, &M, &Q);
	vector<vector<int> > rowlen, collen;
	for(int i = 0; i < N; i++){
		vector<int> tmp;
		for(int j = 0, x; j < M - 1; j++){
			scanf("%d", &x);
			tmp.push_back(x);
		}
		rowlen.push_back(tmp);
	}
	
	for(int i = 0; i < N - 1; i++){
		vector<int> tmp;
		for(int j = 0, x; j < M; j++){
			scanf("%d", &x);
			tmp.push_back(x);
		}
		collen.push_back(tmp);
	}
	
	initialize(N, M, Q, rowlen, collen);
	while(Q--){
		int r, c;
		scanf("%d %d", &r, &c);
		printf(">> %d\n", ask(r, c));
	}
}
*/
