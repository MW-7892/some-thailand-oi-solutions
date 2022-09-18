#include <bits/stdc++.h>
#include "onlineshop.h"
using namespace std;
const int K = 50;
const int rat = 50;

void sell_all(int N){
	int l = 1000, r = 1000000;
	while(l < r){
		int mid = (l + r + 1) >> 1;
		int cnt = 0;
		
		for(int i = 1; i  <= K; i++){
			bool ret = sell_price(mid);
			if(ret) cnt++;
			N--;
		}
		if(cnt >= (K * rat) / 100) l = mid;
		else r = mid - 1;
	}
	while(N--) sell_price(l);
}
