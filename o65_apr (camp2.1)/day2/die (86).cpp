#include <bits/stdc++.h>
using namespace std;

array<int, 3> dp[1001]; // size, from, process (1: add, 2: subtract, 3: mul)

string add_plus(int t){
	string K = "";
	for(int i = 0; i < t; i++) K += "+";
	return K;
}

string mul_k(int k){
	// structure need k + 6
	string ret = "";
	ret += "[>" + add_plus(k) + "<-]>";
	return ret;
}

string add_minus(int t){
	string K = "";
	for(int i = 0; i < t; i++) K += "-";
	return K;
}

string spmul_k(int k){
	// structure need k + 6
	string ret = "";
	ret += "[>" + add_plus(k) + "<-]";
	return ret;
}

string genn(int K){
	// printf(">> %d\n", K);
	// printf("!! %d %d %d\n", dp[K][0], dp[K][1], dp[K][2]);
	if(K == 0) return "";
	string ret = genn(dp[K][1]);
	if(dp[K][2] == 1) return ret + add_plus(K - dp[K][1]);
	if(dp[K][2] == 2) return ret + add_minus(dp[K][1] - K);
	
	return ret + mul_k(K / dp[K][1]);
}

string A(int T, int C){
	string ret = "";
	if(C <= 10){
		ret += add_plus(C);
		return ret;
	}
	
	if(C <= 250){
		for(int q = 0; q < C; q++){
			for(int i = 1; i <= 10; i++) dp[i] = {i, i - 1, 1};
			for(int i = 11; i <= C; i++){
				dp[i][0] = 100000000;
				for(int j = 1; j < i; j++){
					// add
					if(dp[j][0] + (i - j) < dp[i][0]) dp[i] = {dp[j][0] + (i - j), j, 1};
					if(i % j == 0){
						if(dp[j][0] + (6 + (i / j)) < dp[i][0]) dp[i] = {dp[j][0] + (6 + (i / j)), j, 3};
					}
				}
				
			}
			for(int i = C - 1; i >= 11; i--){
				for(int j = C; j > i; j--){
					// sub
					if(dp[j][0] + (j - i) < dp[i][0]) dp[i] = {dp[j][0] + (j - i), j, 2};
				}
				// printf("==> %d : %d %d %d\n", i, dp[i][0], dp[i][1], dp[i][2]);
			}
		}
	}
	
	for(int i = 1; i <= 10; i++) dp[i] = {i, i - 1, 1};
	for(int i = 11; i <= C; i++){
		dp[i][0] = 100000000;
		for(int j = 1; j < i; j++){
			// add
			if(dp[j][0] + (i - j) < dp[i][0]) dp[i] = {dp[j][0] + (i - j), j, 1};
			if(i % j == 0){
				if(dp[j][0] + (6 + (i / j)) < dp[i][0]) dp[i] = {dp[j][0] + (6 + (i / j)), j, 3};
			}
		}
		
	}
	for(int i = C - 1; i >= 11; i--){
		for(int j = C; j > i; j--){
			// sub
			if(dp[j][0] + (j - i) < dp[i][0]) dp[i] = {dp[j][0] + (j - i), j, 2};
		}
		// printf("==> %d : %d %d %d\n", i, dp[i][0], dp[i][1], dp[i][2]);
	}
	
	return genn(C);
}
