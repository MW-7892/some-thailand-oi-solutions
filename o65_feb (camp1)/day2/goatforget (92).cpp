#include <bits/stdc++.h>
#include "goatforget.h"
using namespace std;
vector<int> adj[101];
set<pair<int, int> > ss;
vector<vector<int> > v;
bool vis[101];
int NN;

vector<int> mke(int a, int b){
	vector<int> ret;
	ret.push_back(a); ret.push_back(b);
	return ret;
}

void dfs(int a, int p){
	if(p != -1){
		int a2 = a, b2 = p;
		if(a2 > b2) swap(a2, b2);
		ss.insert({a2, b2});
	}
	set<int> s;
	if(p != -1) s.insert(p);
	s.insert(a);
	int ask = talk_tae(0);
	if(s.find(ask) != s.end()) talk_tae(a);
	else{
		s.insert(ask);
		if(!vis[ask]){
			vis[ask] = true;
			dfs(ask, a);
		}
		else{
			int a2 = ask, b2 = a;
			if(a2 > b2) swap(a2, b2);
			ss.insert({a2, b2});
			talk_tae(a);
		}
	}
	ask = talk_tae(NN - 1);
	if(s.find(ask) != s.end()) talk_tae(a);
	else{
		s.insert(ask);
		if(!vis[ask]){
			vis[ask] = true;
			dfs(ask, a);
		}
		else{
			int a2 = ask, b2 = a;
			if(a2 > b2) swap(a2, b2);
			ss.insert({a2, b2});
			talk_tae(a);
		}
	}
	
	if(s.size() == 1) return;
	bool chk = false;
	queue<int> q;
	set<int> s2;
	while(true){
		int idx = 0, old;
		for(auto x : s){
			if(idx == 0){
				old = x;
				idx++; continue;
			}
			if((x - old + 1) % 2 == 0){
				if(s.find((x + old) >> 1) == s.end() && s2.find((x + old) >> 1) == s2.end()){
					ask = talk_tae((x + old) >> 1);
					if(s.find(ask) != s.end() || s2.find(ask) != s2.end()) talk_tae(a);
					else{
						// printf("c1 %d to %d\n", a, ask);
						chk = true;
						q.push(ask); s2.insert(ask);
						if(!vis[ask]){
							vis[ask] = true;
							dfs(ask, a);
						}
						else{
							int a2 = ask, b2 = a;
							if(a2 > b2) swap(a2, b2);
							ss.insert({a2, b2});
							talk_tae(a);
						}
					}
				} 
				
				if(s.find((x + old + 1) >> 1) == s.end() && s2.find((x + old + 1) >> 1) == s2.end()){
					ask = talk_tae((x + old + 1) >> 1);
					if(s.find(ask) != s.end() || s2.find(ask) != s2.end()) talk_tae(a);
					else{
						// printf("c2 %d to %d\n", a, ask);
						chk = true;
						q.push(ask); s2.insert(ask);
						if(!vis[ask]){
							vis[ask] = true;
							dfs(ask, a);
						}
						else{
							int a2 = ask, b2 = a;
							if(a2 > b2) swap(a2, b2);
							ss.insert({a2, b2});
							talk_tae(a);
						}
					}
				}
				
			}
			else{
				if(s.find((x + old) >> 1) == s.end() && s2.find((x + old) >> 1) == s2.end()){
					ask = talk_tae((x + old) >> 1);
					if(s.find(ask) != s.end() || s2.find(ask) != s2.end()) talk_tae(a);
					else{
						// printf("c3 %d to %d\n", a, ask);
						chk = true;
						q.push(ask); s2.insert(ask);
						if(!vis[ask]){
							vis[ask] = true;
							dfs(ask, a);
						}
						else{
							int a2 = ask, b2 = a;
							if(a2 > b2) swap(a2, b2);
							ss.insert({a2, b2});
							talk_tae(a);
						}
					}
				}
			}
			
			old = x;
			idx++;
		}
		
		if(!chk){
			if(p != -1) talk_tae(p);
			return;
		}
		else{
			while(!q.empty()){
				s.insert(q.front());
				q.pop();
			}
			s2.clear();
			chk = false;
		}
	}
}

vector<vector<int>> recover_map(int N, int M, int Q){
	NN = N;
	vis[0] = true;
	dfs(0, -1);
	for(auto x : ss){
		v.push_back(mke(x.first, x.second));
	}
	/*
	for(auto x : v){
		for(auto y : x){
			printf("%d ", y);
		}
		printf("\n");
	}
	*/
	
	return v;
}
