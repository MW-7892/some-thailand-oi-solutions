#include <bits/stdc++.h>
using namespace std;
long long sum = 0, shift = 0;
priority_queue<long long> L;
priority_queue<long long, vector<long long>, greater<long long>> R;
bool chk = false;
long long old = 0, ymin = 0;

void initialize(int N){
	
}

long long max_hp_loss(int X, int T, int A, int P){
	sum += A * 1ll;
	if(!chk){
		L.push(X * 1ll);
		R.push(X * 1ll);
		old = T * 1ll;
		
		chk = true;
		return sum;
	}
	shift += (P * 1ll) * (T * 1ll - old);
	long long left = L.top() - shift;
	long long right = R.top() + shift;
	
	if(X * 1ll < left){
		ymin += abs(X * 1ll - left);
		R.push(left - shift);
		L.pop();
		
		L.push(X * 1ll + shift);
		L.push(X * 1ll + shift);
	}
	else if(X * 1ll > right){
		ymin += abs(X * 1ll - right);
		L.push(right + shift);
		R.pop();
		
		R.push(X * 1ll - shift);
		R.push(X * 1ll - shift);
	}
	else{
		L.push(X * 1ll + shift);
		R.push(X * 1ll - shift);
	}
	
	old = T * 1ll;
	return sum - ymin;
}
