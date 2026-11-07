/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Description: Thuật toán đơn giản tìm ghép cặp cực đại trên đồ thị hai phía.
 * g[u] chứa danh sách các đỉnh kề thuộc phía phải của đỉnh u ở phía trái.
 * btoa phải được khởi tạo toàn bộ bằng -1 và có kích thước bằng số đỉnh
 * phía phải. Trả về kích thước matching. btoa[v] là đỉnh phía trái được
 * ghép với v, hoặc -1 nếu v chưa được ghép.
 * Time: $O(VE)$
 * Usage: vi btoa(m, -1); dfsMatching(g, btoa);
 * Status: works
 */
#pragma once

bool find(int j, vector<vi> &g, vi &btoa, vi &vis) {
	if (btoa[j] == -1)
		return 1;
	vis[j] = 1;
	int di = btoa[j];
	for (int e : g[di])
		if (!vis[e] && find(e, g, btoa, vis)) {
			btoa[e] = di;
			return 1;
		}
	return 0;
}
int dfsMatching(vector<vi> &g, vi &btoa) {
	vi vis;
	rep(i, 0, sz(g)) {
		vis.assign(sz(btoa), 0);
		for (int j : g[i])
			if (find(j, g, btoa, vis)) {
				btoa[j] = i;
				break;
			}
	}
	return sz(btoa) - (int)count(all(btoa), -1);
}
