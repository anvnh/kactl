/**
 * Author: Anvnh
 * Date: 2026-11-06
 * License: CC0
 * Source: Wikipedia - Floyd–Warshall algorithm
 * Description: Tìm đường đi ngắn nhất giữa mọi cặp đỉnh trên đồ thị có hướng,
 *  có thể chứa cạnh trọng số âm.
 *  Đầu vào là ma trận khoảng cách m, trong đó m[i][j] = inf nếu
 *  không có cạnh trực tiếp từ i đến j.
 *  Sau khi chạy:
 *  - m[i][j] = khoảng cách ngắn nhất từ i đến j.
 *  - m[i][j] = inf nếu không tồn tại đường đi.
 *  - m[i][j] = -inf nếu có thể đi qua chu trình trọng số âm.
 * Time: O(N^3)
 * Status: Tested
 */
#pragma once

const ll inf = 1LL << 62;
void floydWarshall(vector<vector<ll>> &m) {
	int n = sz(m);
	rep(i, 0, n) m[i][i] = min(m[i][i], 0LL);
	rep(k, 0, n) rep(i, 0, n)
		rep(j, 0, n) if (m[i][k] != inf && m[k][j] != inf) {
		auto newDist = max(m[i][k] + m[k][j], -inf);
		m[i][j] = min(m[i][j], newDist);
	}
	rep(k, 0, n) if (m[k][k] < 0) rep(i, 0, n)
		rep(j, 0, n) if (m[i][k] != inf && m[k][j] != inf) m[i][j] = -inf;
}
