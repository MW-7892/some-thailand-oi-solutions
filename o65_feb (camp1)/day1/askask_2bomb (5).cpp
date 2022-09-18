#include <bits/stdc++.h>
#include "askask.h"
using namespace std;

vector<int> find_bombs(int N){
	vector<vector<int> > v;
	for(int i = 0; i < N; i++){
		vector<int> tmp;
		tmp.push_back(i);
		
		v.push_back(tmp);
	}
	vector<bool> k = analyse(v);
	vector<int> ans;
	int cnt = 0;
	for(int i = 0; i < N; i++){
		if(k[i]){
			ans.push_back(i);
			cnt++;
		}
	}
	if(cnt == 1) ans.push_back(ans[0]);
	return ans;
}
