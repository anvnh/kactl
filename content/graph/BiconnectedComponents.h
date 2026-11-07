/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Tìm tất cả các thành phần liên thông hai đỉnh trong đồ thị
 *  vô hướng và gọi callback với danh sách cạnh của từng thành phần.
 *  Trong một thành phần, giữa hai đỉnh bất kỳ có ít nhất hai đường đi
 *  không có đỉnh trong chung. Một đỉnh có thể thuộc nhiều thành phần.
 *  Cạnh không thuộc thành phần nào là cầu, tức không nằm trên chu trình.
 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps([\&](const vi\& edgelist) {...});
 * Time: O(V + E)
 * Status: tested during MIPT ICPC Workshop 2017
 */
#pragma once

vi num, st;
vector<vector<pii>> ed;
int Time;
template <class F> int dfs(int at, int par, F &f) {
	int me = num[at] = ++Time, top = me;
	for (auto [y, e] : ed[at])
		if (e != par) {
			if (num[y]) {
				top = min(top, num[y]);
				if (num[y] < me)
					st.push_back(e);
			} else {
				int si = sz(st);
				int up = dfs(y, e, f);
				top = min(top, up);
				if (up == me) {
					st.push_back(e);
					f(vi(st.begin() + si, st.end()));
					st.resize(si);
				} else if (up < me)
					st.push_back(e);
				else { /* e is a bridge */
				}
			}
		}
	return top;
}

template <class F> void bicomps(F f) {
	num.assign(sz(ed), 0);
	rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1, f);
}
