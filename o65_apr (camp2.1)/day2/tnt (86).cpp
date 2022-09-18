#include <bits/stdc++.h>
#include "tnt.h"
using namespace std;
bool mark[1031][1031], res[1031]; // start, speed
int pos[1031][1031];
int citycnt[1031];
bitset<600001> k[1031];

vector<int> find_truck(int N){
	int left = 0;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			pos[i][j] = (i + j) % N; mark[i][j] = true;
			left++;
		}
	}
	vector<int> ask;
	for(int i = 0; i < N / 2; i++) ask.push_back(i);
	while(left > 1){
		memset(citycnt, 0, sizeof citycnt);
		
		bool q = find_tnt(ask);
		for(int i = 0; i < N; i++) res[i] = !q;
		for(auto x : ask) res[x] = q;
		
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				if(!mark[i][j]) continue;
				if(!res[pos[i][j]]){
					mark[i][j] = false;
					left--;
				}
				else{
					pos[i][j] = (pos[i][j] + j) % N;
					citycnt[pos[i][j]]++;
				}
			}
		}
	
		
		ask.clear();
		
		for(int i = 0; i < N; i++){
			k[i] &= 0;
			
			if(i == 0) k[i][citycnt[i]] = k[i][0] = 1;
			else k[i] = k[i - 1] | (k[i - 1] << citycnt[i]);
			
//			printf(">> %d : %d\n", i, citycnt[i]);
//			
//			for(int j = 0; j <= left / 2; j++){
//				printf(k[i][j] ? "1 " : "0 ");
//			}
//			printf("\n");
			
			if(k[i][left / 2]){
				int cur = left / 2;
				while(i >= 0){
					if(k[i][cur] && !k[i - 1][cur]){
						ask.push_back(i);
						cur -= citycnt[i];
					}
					i--;
				}
				break;
			}
			
			if((left % 2) && k[i][left / 2 - 1]){
				int cur = left / 2 - 1;
				while(i >= 0){
					if(k[i][cur] && !k[i - 1][cur]){
						ask.push_back(i);
						cur -= citycnt[i];
					}
					i--;
				}
				break;
			}
		}
		
		
		int smmm = 0;
		for(auto x : ask){
			smmm += citycnt[x];
		}
		
		memset(res, 0, sizeof res);
	}
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(mark[i][j]) return {i, j};
		}
	}
}
