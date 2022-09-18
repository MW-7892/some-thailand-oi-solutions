#include <bits/stdc++.h>
#define ii pair<long long, long long>
using namespace std;
deque<ii> a, b;

long long dual_fuel(int N, int V, vector<int> A, vector<int> B){
	long long ans = 0;
	for(int i = 0; i < N; i++){
		while(!a.empty() && a.front().second < i - V) a.pop_front();
		while(!b.empty() && b.front().second < i - V) b.pop_front();
		
		while(!a.empty() && a.back().first >= A[i]) a.pop_back();
		while(!b.empty() && b.back().first >= B[i]) b.pop_back();
		a.push_back({A[i], i});
		b.push_back({B[i], i});
		
		ans += a.front().first + b.front().first;
	}
	return ans;
}
