#include <bits/stdc++.h>
using namespace std;
long long dp[100001], sm[100001], smsq[100001], rev[100001];

long long destroy_bridge(int N, vector<int> W){
	for(int i = 0; i < N; i++){
		if(i > 0){
			sm[i] = sm[i - 1]; smsq[i] = smsq[i - 1];
		}
		sm[i] += (W[i] * 1ll);
		smsq[i] += (W[i] * 1ll) * (W[i] * 1ll);
		
		dp[i] = ((sm[i] * sm[i]) - (smsq[i])) >> 1;
		for(int j = i - 1; j >= 0; j--){
			dp[i] = min(dp[i], ((sm[i] - sm[j]) * (sm[i] - sm[j]) - (smsq[i] - smsq[j])) >> 1);
		}
		if(i > 0) dp[i] = min(dp[i], dp[i - 1]);
	}
	long long ans = LLONG_MAX;
	memset(sm, 0, sizeof sm); memset(smsq, 0, sizeof smsq);
	for(int i = N - 1; i > 1; i--){
		if(i < N - 1){
			sm[i] = sm[i + 1]; smsq[i] = smsq[i + 1];
		}
		sm[i] += (W[i] * 1ll);
		smsq[i] += (W[i] * 1ll) * (W[i] * 1ll);
		
		rev[i] = ((sm[i] * sm[i]) - (smsq[i])) >> 1;
		for(int j = i + 1; j < N; j++){
			rev[i] = min(rev[i], ((sm[i] - sm[j]) * (sm[i] - sm[j]) - (smsq[i] - smsq[j])) >> 1);
		}
		if(i < N - 1) rev[i] = min(rev[i], rev[i + 1]);
		
		ans = min(ans, rev[i] + dp[i - 2]);
	}
	return ans;
}
