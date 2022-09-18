#include <bits/stdc++.h>
#define ii pair<unsigned long long, unsigned long long>
using namespace std;
vector<ii> convex(5000001);

bool is_left(ii a, ii b, ii c){
	// positive = left, negative = right, 0 = straight
	unsigned long long x1 = b.first - a.first, y1 = b.second - a.second;
	unsigned long long x2 = c.first - b.first, y2 = c.second - b.second;
	return (x1 * y2) >= (x2 * y1);
}

vector<long long> max_revenue(int N, int K, vector<long long> X, vector<int> M){
	vector<long long> ans;
	convex[0] = {0, X[0]};
	int idx = 1; unsigned long long curmax = X[0] * 1llu;
	for(int i = 1; i < N; i++){
		if(X[i] * 1llu < curmax) continue;
		curmax = max(curmax, X[i] * 1llu);
		while(idx >= 2 && is_left(convex[idx - 2], convex[idx - 1], {i * 1llu, X[i] * 1llu})){
			// printf("%d : pop %d >> %lld %lld\n", i, idx - 1, convex[idx - 1].first, convex[idx - 1].second);
			idx--;
		}
		convex[idx++] = {i, X[i]};
	}
	// for(int i = 0; i < idx; i++) printf("%d %d\n", convex[i].first, convex[i].second);
	int ptr = 0;
	for(int i = idx - 1; i > 0; i--){
		while(ptr < N && convex[i].second - convex[i - 1].second >= (M[ptr] * 1ll) * (convex[i].first - convex[i - 1].first)){
			ans.push_back(convex[i].second - (M[ptr] * 1ll) * convex[i].first);
			ptr++;
		}
	}
	while(ptr < N){
		ans.push_back(X[0]);
		ptr++;
	}
	return ans;
}
