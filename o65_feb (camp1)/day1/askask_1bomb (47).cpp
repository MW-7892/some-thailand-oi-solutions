#include <bits/stdc++.h>
#include "askask.h"
using namespace std;
vector<vector<int> > a;
vector<int> tmp[11];
/*
int x_1, x_2;
int n, q;

std::vector<bool> analyse(std::vector<std::vector<int>> Z){
  q = Z.size();
  if(q > n){
    std::cout << "Invalid Query: too many queries" << std::endl;
    exit(0);
  }
  std::vector<bool> output;
  output.reserve(q);
  for(std::vector<int>& S : Z){
    if(S.size() > n){
      std::cout << "Invalid Query: invalid query" << std::endl;
      exit(0);
    }
    sort(S.begin(), S.end());
    int last = -1;
    bool found = false;
    for(int y : S){
      if(last != -1 && last == y){
        std::cout << "Invalid Query: invalid query" << std::endl;
        exit(0);
      }
      if(y < 0 || y >= n){
        std::cout << "Invalid Query: invalid query" << std::endl;
        exit(0);
      }
      last = y;
      if(y == x_1 || y == x_2) found = true;
    }
    output.push_back(found);
  }
  return output;
}
*/
void gen(int K, int idx){
	if(K == 2){
		tmp[1].push_back(idx);
		tmp[1].push_back(idx + 1);
		
		tmp[2].push_back(idx + 1);
		tmp[2].push_back(idx + 2);
		
		return;
	}
	for(int i = idx; i < idx + (1 << (K - 1)); i++){
		tmp[K].push_back(i);
	}
	gen(K - 1, idx);
	gen(K - 1, idx + (1 << (K - 1)));
	return;
}

vector<int> find_bombs(int N){
	if(N == 2){
		vector<int> tmp2;
		vector<vector<int> > tmp3;
		tmp2.push_back(0);
		tmp3.push_back(tmp2);
		
		vector<bool> k = analyse(tmp3);
		vector<int> ret;
		if(k[0]){
			ret.push_back(0);
			ret.push_back(0);
		}
		else{
			ret.push_back(1);
			ret.push_back(1);
		}
		return ret;
	}
	
	int Q = int(log2(N));
	
	gen(Q, 0);
	for(int i = 1; i <= Q; i++){
		sort(tmp[i].begin(), tmp[i].end());
		a.push_back(tmp[i]);
		tmp[i].clear();
	}
	vector<bool> k = analyse(a);
	a.clear();
	
	int ans = 0;
	for(int i = Q - 1; i > 1; i--){
		if(!k[i]) ans += (1 << i);
	}
	if(k[0] && k[1]) ans++;
	else if(k[1] && !k[0]) ans += 2;
	else if(!k[0] && !k[1]) ans += 3;
	
	vector<int> ret;
	ret.push_back(ans);
	ret.push_back(ans);
	
	return ret;
}
/*
int main(){
  std::ios::sync_with_stdio(false);
  std::cin >> n >> x_1 >> x_2;
  if(x_1 > x_2) std::swap(x_1, x_2);
  std::vector<int> output = find_bombs(n);
  if(output.size() != 2){
    std::cout << "Wrong Answer: output size is not 2" << std::endl;
    exit(0);
  }
  if(output[0] != x_1 || output[1] != x_2){
    std::cout << "Wrong Answer: expected " << x_1 << " " << x_2 << " but found " << output[0] << " " << output[1] << std::endl;
    exit(0);
  }
  std::cout << "Correct Answer: " << q << std::endl;
  return 0;
}
*/
