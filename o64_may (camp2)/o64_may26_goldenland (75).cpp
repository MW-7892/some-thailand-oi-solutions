#include <bits/stdc++.h>
using namespace std;
map<vector<int>, int> mp;
bitset<1000001> sieve;
int chk[1000001];
int cnts[60001];
vector<int> A, B, primes;
int cnt = 1;
int sqN, sqM;
int blocks[850][21];

void init_land(int N, int M, int P, vector<int> a, vector<int> b){
	sqN = int(ceil(sqrt(N)));
	sqM = int(ceil(sqrt(M)));
	A = a, B = b;
	for(int i = 2; i <= 1000000; i++){
		if(sieve[i]) continue;
		for(long long j = (i * 1ll) * (i * 1ll); j <= 1000000 * 1ll; j += (i * 1ll)){
			sieve[j] = 1;
		}
		primes.push_back(i);
	}
	for(int i = 0; i < N; i++){
		int x = A[i];
		if(!chk[x]){
			int tmp_x = x;
			vector<int> fact;
			for(auto y : primes){
				if(y > tmp_x) break;
				int cnt = 0;
				while(tmp_x >= y && tmp_x % y == 0){
					tmp_x /= y;
					cnt++;	
				}
				if(cnt % 2 == 1) fact.push_back(y);
			}
			if(mp.find(fact) != mp.end()) A[i] = mp[fact];
			else{
				A[i] = cnt;
				mp[fact] = cnt++;
			}
			chk[x] = mp[fact];
		}
		else A[i] = chk[x];
	}
	
	for(int i = 0; i < M; i++){
		int x = B[i];
		if(!chk[x]){
			int tmp_x = x;
			vector<int> fact;
			for(auto y : primes){
				if(y > tmp_x) break;
				int cnt = 0;
				while(tmp_x >= y && tmp_x % y == 0){
					tmp_x /= y;
					cnt++;	
				}
				if(cnt % 2 == 1) fact.push_back(y);
			}
			if(mp.find(fact) != mp.end()) B[i] = mp[fact];
			else{
				B[i] = cnt;
				mp[fact] = cnt++;
			}
			chk[x] = mp[fact];
		}
		else B[i] = chk[x];
	}
	
	// sqrt decomposition
}

long long answer_query(int r1, int c1, int r2, int c2){
	for(int i = r1; i <= r2; i++) cnts[A[i]]++;
	long long ans = 0;
	for(int i = c1; i <= c2; i++) ans += (cnts[B[i]] * 1ll);
	for(int i = 0; i <= cnt; i++) cnts[i] = 0;
	return ans;
}

/*
8 8 10
5 4 1 2 8 9 3 7
2 1 4 3 8 6 5 2
0 1 1 3
0 4 3 4
0 7 0 7
1 6 1 7
2 6 4 7
6 6 7 7
7 0 7 4
4 2 5 4
4 0 5 0
2 0 3 2
*/
