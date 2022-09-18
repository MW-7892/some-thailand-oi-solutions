#include <bits/stdc++.h>
#define ii pair<int, int>
#define pi pair<int, ii>
using namespace std;
pi a[1000001];

pi dfs(int k){
	if(k == 1) return a[1];
	if(a[k].first != 0) return a[k];
	for(int i = 1; i < k; i++){
		if(k % i == 0){
			pi tmp = dfs(i);
			if(a[k].first == 0 || a[k].first > tmp.first + (k / i)){
				a[k] = make_pair(tmp.first + (k / i), make_pair(k / i, i));
			}
		}
	}
	return a[k];
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	ifstream cin("test.in"); ofstream cout("test.out");
	int N, T;
	cin >> T;
	int ik = 1;
	while(T--){
	cin >> N;
	dfs(N);
	int j = N;
	stack<ii> stk;
	while(j != 1){
		stk.push(make_pair(1, a[j].second.first));
		stk.push(make_pair(0, 0));
		// printf("%d :\n total = %d\n paste val = %d\n no = %d\n", j, a[j].first, a[j].second.first, a[j].second.second);
		j = a[j].second.second;
	}
	cout << ik << "\n";
	while(!stk.empty()){
		if(stk.top().first == 1){
			for(int i = 1; i <= stk.top().second; i++) cout << "V";
		}
		else{
			cout << "AC";
		}
		stk.pop();
	}
	cout << "\n";
	ik++;
	}
}
