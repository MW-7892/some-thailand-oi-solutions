#include <bits/stdc++.h>
using namespace std;
long long dp[2002][2002]; // diff, min
long long md = 1e9 + 7;
long long e2[1000001];
long long sm[2002];

long long C[2002][2002];

int find_ans(vector<int> num){
	sort(num.begin(), num.end());
	int len = num.size();
	
	vector<pair<int, int> > a;
	a.push_back({num[0], 1});
	
	for(int i = 1; i < len; i++){
		if(num[i] == a.back().first) a.back().second++;
		else a.push_back({num[i], 1});
	}
	for(int i = 0; i <= len; i++) e2[i]--;
	
	len = a.size();
	int N = len;
	
	for(int i = 1; i <= N; i++){
		C[i][0] = 1;
		C[i][i] = 1;
		for(int j = 1; j < i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % md;
	}
	
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= i; j++) C[i][j] = (C[i][j] * ((j + 2) * 1ll)) % md;
		// printf(">>>> %d %d : %lld\n", i, j, C[i][j]);}
		for(int j = 2; j <= i; j++) C[i][j] = (C[i][j] + C[i][j - 1]) % md;
	}
	
	long long ans = 0;
	for(int l = 1; l < N; l++){
		for(int i = 1; i + l <= N; i++){
			if(l == 1) ans += (l + 1) * 1ll;
			else{
				ans = (ans + ((2) * l * 1ll)) % md;
				ans = (ans + (C[l - 1][l - 1] * l)) % md;
			}
			// printf("%d %d : %lld\n", i, i + l, (l + 1) + (C[l - 1][l - 1] * l));
		}
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
