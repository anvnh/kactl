/**
 * Author: Simon Lindholm
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore
 * Description: Tìm đường đi hoặc chu trình Euler trong đồ thị có hướng
 *  hoặc vô hướng bằng thuật toán Hierholzer. Đồ thị được biểu diễn bằng
 *  danh sách các cặp (đỉnh đến, ID cạnh toàn cục). Với đồ thị vô hướng,
 *  hai chiều của cùng một cạnh phải có chung ID. Trả về dãy đỉnh trên
 *  đường đi Euler, hoặc dãy rỗng nếu không tồn tại. Nếu cần lấy ID cạnh,
 *  lưu thêm .second vào stack s và kết quả ret.
 * Time: O(V + E)
 * Status: stress-tested
 */
#pragma once

vi eulerWalk(vector<vector<pii>> &gr, int nedges, int src = 0) {
	int n = sz(gr);
	vi D(n), its(n), eu(nedges), ret, s = {src};
	D[src]++; // to allow Euler paths, not just cycles
	while (!s.empty()) {
		int x = s.back(), y, e, &it = its[x], end = sz(gr[x]);
		if (it == end) {
			ret.push_back(x);
			s.pop_back();
			continue;
		}
		tie(y, e) = gr[x][it++];
		if (!eu[e]) {
			D[x]--, D[y]++;
			eu[e] = 1;
			s.push_back(y);
		}
	}
	for (int x : D)
		if (x < 0 || sz(ret) != nedges + 1)
			return {};
	return {ret.rbegin(), ret.rend()};
}
