/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Kiểm tra điểm p có nằm bên trong đa giác hay không.
 *  Nếu strict = true, trả về false đối với điểm nằm trên biên đa giác.
 *  Thuật toán sử dụng các phép nhân trung gian nên cần chú ý tràn số.
 * Time: O(n)
 * Usage:
 *  vector<P> v = {P{4,4}, P{1,2}, P{2,1}};
 *  bool in = inPolygon(v, P{3, 3}, false);
 * Status: Đã kiểm thử ngẫu nhiên cường độ cao và kiểm thử trên Kattis:
 * pointinpolygon
 */
#pragma once

#include "OnSegment.h"
#include "Point.h"
#include "SegmentDistance.h"

template <class P> bool inPolygon(vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = sz(p);
	rep(i, 0, n) {
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a))
			return !strict;
		// or: if (segDist(p[i], q, a) <= eps) return !strict;
		cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}
