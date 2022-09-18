#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> diff, rev;
vector<double> area;

long long maximum_incompatibility(vector<vector<int>> A){
	// M pieces, N size per piece
	int M = A.size();
	int N = A[0].size();
	
	for(int i = 0; i < M; i++){
		// get diff;
		vector<int> tmp, tmp2;
		tmp.push_back(1000000000 + i + 1);
		for(int j = 1; j < N; j++) tmp.push_back(A[i][j] - A[i][j - 1]);
		tmp.push_back(-1 - i);
		
		for(int j = N; j >= 0; j--) tmp2.push_back(tmp[j]);
		
		diff.push_back(tmp); rev.push_back(tmp2);
		
		// get area
		double tmp_a = 0;
		for(int j = 1; j < N; j++){
			tmp_a += double(A[i][j] - A[i][j - 1]) / double(2) + double(A[i][j - 1]);
		}
		area.push_back(tmp_a);
	}
	
	double ans = double(0);
	for(int i = 0; i < M; i++){
		for(int j = i + 1; j < M; j++){
			// i up, j reverse
			int l = 0, r = N - 1;
			while(l < r){
				int mid = (l + r) >> 1;
				
				if(diff[i][mid] >= rev[j][mid]){
					if(diff[i][mid] == rev[j][mid]){
						l = r = mid - 1;
						break;
					}
					
					if(diff[i][mid + 1] > rev[j][mid + 1]) l = mid + 1;
					else{
						l = r = mid;
						break;
					}
				}
				else if(diff[i][mid] < rev[j][mid]) r = mid - 1;
			}
			
			long long rect_height = A[i][l] + A[j][N - l - 1];
			double rect_a = double(rect_height * ((N - 1) * 1ll));
			
			ans = max(ans, double(2) * (rect_a - area[i] - area[j]));
		}
	}
	return (long long)(ans);
}
