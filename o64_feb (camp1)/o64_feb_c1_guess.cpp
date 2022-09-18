#include <bits/stdc++.h>
#include "guess.h"
using namespace std;
bool vis[1024];

/*
int KK = 242;
int cnt = 0;


char ask(vector<pair<int, char> > ab){
	cnt++;
	bool chk = false;
	for(auto x : ab){
		if(x.first == KK) return x.second;
		else if(x.first == KK - 1 || x.first == KK + 1) chk = true;
	}
	if(chk) return 'C';
	return 'X';
}
*/

int find_answer(int N, int K){
	if(N == 729){
		vector<int> vv;
		for(int i = 0; i < 729; i++) vv.push_back(i);
		int len = vv.size();
		
		while(len > 1){
			int len3 = len / 3;
			
			vector<pair<int, char> > a;
			for(int i = 0; i < len3 * 2; i++){
				if(i % 2 == 0){
					a.push_back(make_pair(vv[i], 'R'));
					vis[vv[i]] = true;
				}
				else{
					if(!vis[vv[i] - 1]) a.push_back(make_pair(vv[i] - 1, 'R'));
				}
			}
			memset(vis, 0, sizeof vis);
			
			/*
			for(auto x : a){
				printf("%d ", x.first);
			}
			printf("\n\n");
			*/
			
			char k = ask(a);
			vector<int> tmp;
			if(k == 'X'){
				for(int i = len3 * 2; i < len; i++) tmp.push_back(vv[i]);
			}
			else if(k == 'R'){
				for(int i = 0; i < len3 * 2; i += 2) tmp.push_back(vv[i]);
			}
			else{
				for(int i = 1; i < len3 * 2; i += 2) tmp.push_back(vv[i]);
			}
			
			vv.clear();
			for(auto x : tmp) vv.push_back(x);
			
			len = vv.size();
		}
		return vv[0];
	}
	if(N == 1024 && K == 1){
		int l = 0, r = 1023;
		while(l < r){
			int mid = (l + r) >> 1;
			vector<pair<int, char> > a;
			for(int i = l; i <= mid; i++){
				a.push_back(make_pair(i, 'R'));
			}
			char k = ask(a);
			if(k == 'R') r = mid;
			else l = mid + 1;
		}
		return l;
	}
	else{
		vector<int> v;
		for(int i = 0; i < 1024; i++) v.push_back(i);
		while(v.size() > 1){
			int len = v.size();
			int len4 = len / 4;
			
			vector<pair<int, char> > a;
			for(int i = 0; i < len4 * 3; i++){
				if(i % 3 == 0){
					a.push_back({v[i], 'R'});
					vis[v[i]] = true;
				}
				else if(i % 3 == 1){
					a.push_back({v[i], 'B'});
					vis[v[i]] = true;
				}
				else{
					if(!vis[v[i] - 1]) a.push_back({v[i] - 1, 'R'});
				}
			}
			memset(vis, 0, sizeof vis);
			
			char k = ask(a);
			
			vector<int> tmp;
			if(k == 'R'){
				for(int i = 0; i < len4 * 3; i += 3) tmp.push_back(v[i]);
			}
			else if(k == 'B'){
				for(int i = 1; i < len4 * 3; i += 3) tmp.push_back(v[i]);
			}
			else if(k == 'X'){
				for(int i = len4 * 3; i < len; i++) tmp.push_back(v[i]);
			}
			else{
				for(int i = 2; i < len4 * 3; i += 3) tmp.push_back(v[i]);
			}
			
			v.clear();
			for(auto x : tmp) v.push_back(x);
		}
		return v[0];
	}
}

/*
int main(){
	for(int i = 247; i < 248; i++){
		KK = i;
		printf(">> %d %d\n", find_answer(1024, 2), cnt);
	}	
}
*/
