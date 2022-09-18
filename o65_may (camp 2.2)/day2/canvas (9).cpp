#include <bits/stdc++.h>
#include "canvas.h"

#define co compass
#define st straightedge
#define in intersection

using namespace std;

vector<node> tx, ty;
int rootx, rooty;

//int dfs(int a){
//	if(ty[a].value != -999) return 1;
//}

point draw(string x, string y) {
	pair<vector<node>, int> res1 = parse(x);
	pair<vector<node>, int> res2 = parse(y);
	
	vector<node> tx = res1.first;
	int rootx = res1.second;
	
	vector<node> ty = res2.first;
	int rooty = res2.second;
	
	circle r1_OR = co(p0, p1);
	line y_AX = st(p0, p1);
	
	point y1_pos = in(r1_OR, y_AX, 0);
	point y1_neg = in(r1_OR, y_AX, 1);
	if(y1_pos.y < y1_neg.y) swap(y1_pos, y1_neg);
	
	circle tmp_c1 = co(y1_pos, y1_neg), tmp_c2 = co(y1_neg, y1_pos);
	point x2_pos = in(tmp_c1, tmp_c2, 0);
	point x2_neg = in(tmp_c1, tmp_c2, 1);
	if(x2_pos.x < x2_neg.x) swap(x2_pos, x2_neg);
	
	line x_AX = st(x2_neg, x2_pos);
	point x1_pos = in(r1_OR, x_AX, 0);
	point x1_neg = in(r1_OR, x_AX, 1);
	if(x1_neg.x > x1_pos.x) swap(x1_pos, x1_neg);
	
	if(tx[rootx].value == 0 && ty[rooty].value == 0) return p0;
	
	int goalx = tx[rootx].value, goaly = ty[rooty].value;
	if(ty[rooty].value == -999) goaly = -ty[ty[rooty].right].value;
	if(tx[rootx].value == -999) goalx = -tx[tx[rootx].right].value;
	
	circle co_x, co_y;
	point cur, old, endx, endy;
	
	if(goaly > 0){
		cur = y1_pos, old = p0;
		for(int i = 1; i < goal; i++){
			circle tmp_ci = co(cur, old);
			old = cur;
			cur = in(tmp_ci, y_AX, 1);
		}
		endy = cur;
		co_y = co(cur, p0);
	}
	else if(goaly < 0){
		goaly = -goaly;
		cur = y1_neg, old = p0;
		for(int i = 1; i < goal; i++){
			circle tmp_ci = co(cur, old);
			old = cur;
			cur = in(tmp_ci, y_AX, 1);
		}
		endy = cur;
		co_y = co(cur, p0);
	}
	
	if(goalx > 0){
		cur = x1_pos, old = p0;
		for(int i = 1; i < goal; i++){
			circle tmp_ci = co(cur, old);
			old = cur;
			cur = in(tmp_ci, x_AX, 1);
		}
		endx = cur;
		co_x = co(cur, p0);
	}
	else if(goalx < 0){
		goalx = -goalx;
		cur = x1_neg, old = p0;
		for(int i = 1; i < goal; i++){
			circle tmp_ci = co(cur, old);
			old = cur;
			cur = in(tmp_ci, x_AX, 1);
		}
		endx = cur;
		co_x = co(cur, p0);
	}
	
	if(goalx == 0) return endy;
	if(goaly == 0) return endx;
	
	return in(co_x, co_y, 1);
}
