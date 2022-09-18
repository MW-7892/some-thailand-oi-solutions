#include "tnt.h"
#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
int n;
vector<pair<int,pair<int,int> > > vec1, vec2;
vector<int> Q[2000];

int cal(int a,int b,int t){
	return (a + (b * t)) % n;
}
vector<int>find_truck(int N){
    n = N;
    for(int i=0;i<n;i++){
    	for(int j=0;j<=i;j++){
    		Q[i].push_back(j);
		}
	}
	
    for(int i=0;i<n;i++){
    	for(int j=0;j<n;j++){
    		vec1.push_back({cal(i,j,1),{i,j}});
		}
	}
	
	int t = 2, arr[2030], arr2[2000], hsh[2030], siz;
	while(vec1.size() > 1){
		sort(vec1.begin(),vec1.end());
		vec2.clear();
		
		siz = 0;
		memset(arr,0,sizeof arr);
		memset(hsh,0,sizeof hsh);
		
		for(auto x : vec1){
			hsh[x.F]++;
		}
		
		vector<int> QQ;
		for(int i=0;i<n;i++){
			if(hsh[i] == 0) continue;
			if(siz + hsh[i] <= vec1.size()/2){
				siz += hsh[i];
				arr[i] = 1;
				QQ.push_back(i);
			}
		}
		
		vector<int> QQ2;
		memset(arr2,0,sizeof arr2);
		int siz2 = 0;
		
		for(int i=n;i>=0;i--){
			if(hsh[i] == 0) continue;
			if(siz2 + hsh[i] <= vec1.size()/2){
				siz2 += hsh[i];
				arr2[i] = 1;
				QQ2.push_back(i);
			}
		}
		
		if(siz2 > siz){
			QQ = QQ2;
			for(int i=0;i<n;i++) arr[i] = arr2[i];
		}
		
		bool val = find_tnt(QQ);
//		printf("!! %d\n",vec1.size());
		
		if(val){
			for(auto x : vec1){
				if(arr[x.F]){
					vec2.push_back({cal(x.S.F,x.S.S,t),{x.S.F,x.S.S}});
				}
			}
		}
		else{
			for(auto x : vec1){
				if(!arr[x.F]){
					vec2.push_back({cal(x.S.F,x.S.S,t),{x.S.F,x.S.S}});
				}
			}
		}
		vec1 = vec2;
		t++;
	}
	
	vector<int> ans;
	ans.push_back(vec1[0].S.F);
	ans.push_back(vec1[0].S.S);
    return ans;
}
