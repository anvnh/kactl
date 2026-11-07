/**
 * Author: Anvnh
 * Date: 2026-11-06
 * License: CC0
 * Source: predates tinyKACTL
 * Description: Sắp xếp topo trên đồ thị có hướng.
 *  Kết quả là thứ tự các đỉnh sao cho mọi cạnh đều hướng từ trái sang phải.
 *  Nếu đồ thị có chu trình, danh sách trả về sẽ có ít hơn n đỉnh;
 *  các đỉnh có thể đi tới từ chu trình cũng sẽ không được trả về.
 * Time: O(V + E)
 * Status: stress-tested
 */
#pragma once

vi topoSort(const vector<vi> &gr) {
	vi indeg(sz(gr)), q;
	for (auto &li : gr)
		for (int x : li)
			indeg[x]++;
	rep(i, 0, sz(gr)) if (indeg[i] == 0) q.push_back(i);
	rep(j, 0, sz(q)) for (int x : gr[q[j]]) if (--indeg[x] == 0) q.push_back(x);
	return q;
}
