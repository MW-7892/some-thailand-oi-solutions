#include <bits/stdc++.h>
#define ar array<int, 3>
using namespace std;
vector<vector<int>> v;

int main(){
	for(int tc = 1; tc <= 10; tc++){
		string tmp = to_string(tc);
		if(tc < 10) tmp = "0" + tmp;
		ifstream cin(tmp + ".in"); ofstream cout("output_" + tmp + ".txt");
		int N, M;
		cin >> N >> M;
		for(int i = 0; i < M; i++){
			vector<int> q;
			for(int i = 0, x; i < N; i++){
				cin >> x;
				q.push_back(x);
			}
			int res; cin >> res;
			
			vector<int> r;
			if(res == 1){
				for(int i = 0; i < N; i++){
					if(q[i] == 0) r.push_back(-(i + 1));
					else r.push_back(i + 1);
				}
				bool chk = false;
				for(auto x : v){
					bool chk2 = true;
					for(int i = 0; i < N; i++){
						if(x[i] != -r[i]){
							chk2 = false;
							break;
						}
					}
					if(chk2){
						chk = true;
						break;
					}
				}
				if(!chk) v.push_back(r);
			}
		}
		cout << v.size() << "\n";
		for(auto x : v){
			cout << x.size() << " ";
			for(auto y : x) cout << y << " ";
			cout << "\n";
		}
		v.clear();
	}
}
