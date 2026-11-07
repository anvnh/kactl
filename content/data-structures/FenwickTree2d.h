/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Tính tổng tiền tố các phần tử a[i][j] với i < I, j < J
 *  và hỗ trợ cập nhật giá trị của một phần tử a[i][j].
 *  Cần biết trước các vị trí sẽ được cập nhật: gọi fakeUpdate() cho
 *  tất cả các vị trí đó trước khi gọi init().
 * Time: $O(\log^2 N)$. (Dùng Persistent Segment Tree để đạt $O(\log N)$.)
 * Status: stress-tested
 */
#pragma once

#include "FenwickTree.h"

struct FT2 {
	vector<vi> ys;
	vector<FT> ft;
	FT2(int limx) : ys(limx) {}
	void fakeUpdate(int x, int y) {
		for (; x < sz(ys); x |= x + 1)
			ys[x].push_back(y);
	}
	void init() {
		for (vi &v : ys)
			sort(all(v)), ft.emplace_back(sz(v));
	}
	int ind(int x, int y) {
		return (int)(lower_bound(all(ys[x]), y) - ys[x].begin());
	}
	void update(int x, int y, ll dif) {
		for (; x < sz(ys); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	ll query(int x, int y) {
		ll sum = 0;
		for (; x; x &= x - 1)
			sum += ft[x - 1].query(ind(x - 1, y));
		return sum;
	}
};
