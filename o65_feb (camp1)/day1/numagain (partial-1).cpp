#include <bits/stdc++.h>
using namespace std;
long long dp[2002][2002]; // diff, min
long long md = 1e9 + 7;
long long e2[1000001];

int find_ans(vector<int> num){
	sort(num.begin(), num.end());
	int len = num.size();
	
	vector<pair<int, int> > a;
	a.push_back({num[0], 1});
	e2[0] = 1;
	
	int sz = 0;
	for(int i = 1; i < len; i++){
		e2[i] = (e2[i - 1] * (2 * 1ll)) % md;
		if(num[i] == a[sz].first) a[sz].second++;
		else{
			a.push_back({num[i], 1});
			sz++;
		}
	}
	for(int i = 0; i <= len; i++) e2[i] = (e2[i] - 1 + md) % md;
	
	len = a.size();
	
	long long ans = 0;
	
	for(int i = 0; i < len; i++){
		for(int j = i; j > 0; j--){
			for(int k = 0; k < len; k++){
				if(a[k].first >= a[i].first) break;
				
				long long tmp = (dp[j][a[k].first] * e2[a[i].second]) % md;
				tmp = tmp * ((a[i].first - a[k].first) * 1ll + md) % md;
				tmp = tmp * ((j + 1) * 1ll) % md;
				ans = (ans + tmp) % md;
				
				dp[j + 1][a[k].first] = (dp[j + 1][a[k].first] + (dp[j][a[k].first] * e2[a[i].second]) % md) % md;
			}
		}
		dp[1][a[i].first] = e2[a[i].second];
	}
	
	return ans;
}

/*
int main()
{
    int N;
    scanf("%d",&N);
    std::vector<int>number(N);
    for(int i = 0;i < N;i++)
    {
        scanf("%d",&number[i]);
    }
    printf("%d\n",find_ans(number));
    return 0;
}
*/
