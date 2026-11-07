/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: tinyKACTL
 * Description: Tính hai lần diện tích có dấu của đa giác.
 *  Các đỉnh được liệt kê theo chiều kim đồng hồ cho kết quả âm.
 *  Cần chú ý tràn số nếu T là int.
 * Status: Đã kiểm thử ngẫu nhiên cường độ cao và kiểm thử trên Kattis:
 * polygonarea
 */
#pragma once

#include "Point.h"

template <class T> T polygonArea2(vector<Point<T>> &v) {
	T a = v.back().cross(v[0]);
	rep(i, 0, sz(v) - 1) a += v[i].cross(v[i + 1]);
	return a;
}
