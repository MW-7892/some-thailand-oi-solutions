#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;
int pa[200001], h[200001];
ii up[200001];
int timer = 0;

int findpa(int a){
	return pa[a] == a ? a : pa[a] = findpa(pa[a]);
}

void cheat(int p1, int p2){
	timer++;
	
	if(pa[p1] == 0) pa[p1] = p1;
	if(pa[p2] == 0) pa[p2] = p2;
	
	if(findpa(p1) == findpa(p2)) return;
	if(h[findpa(p1)] < h[findpa(p2)]) swap(p1, p2);
	
	h[findpa(p1)] = max(h[findpa(p1)], h[findpa(p2)] + 1);
	up[findpa(p2)] = make_pair(findpa(p1), timer);
	pa[findpa(p2)] = findpa(p1);
}

int investigate(int p1, int p2){
	if(pa[p1] == 0) pa[p1] = p1;
	if(pa[p2] == 0) pa[p2] = p2;
	
	if(findpa(p1) != findpa(p2)) return -1;
	int l = 1, r = timer;
	while(l < r){
		int mid = (l + r) >> 1;
		int t1 = p1, t2 = p2;
		while(up[t1].first != 0 && up[t1].second <= mid){
			// printf("p1 : %d --> %d, %d\n", t1, up[t1].first, up[t1].second);
			t1 = up[t1].first;
		}
		while(up[t2].first != 0 && up[t2].second <= mid){
			// printf("p2 : %d --> %d, %d\n", t2, up[t2].first, up[t2].second);
			t2 = up[t2].first;
		}
		
		// printf(">> %d %d %d >> %d %d\n", l, r, mid, p1, p2);
		
		if(t1 != t2) l = mid + 1;
		else r = mid;
	}
	return l;
}

/*
int main(){
	while(true){
		int x;
		scanf("%d", &x);
		if(x == 0) break;
		
		if(x == 1){
			int a, b;
			scanf("%d %d", &a, &b);
			cheat(a, b);
		}
		if(x == 2){
			int a, b;
			scanf("%d %d", &a, &b);
			printf(">> %d\n", investigate(a, b));
		}
	}
}
*/
