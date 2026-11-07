/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description: Xác định vị trí của điểm $p$ khi nhìn từ $s$ theo hướng đến $e$.
 *  Trả về 1/0/-1 tương ứng với: bên trái / trên đường thẳng / bên phải.
 *  Nếu có tham số tùy chọn $eps$, trả về 0 nếu $p$ cách đường thẳng một khoảng
 * không quá $eps$. P được giả định là Point<T>, trong đó T có thể là double
 * hoặc long long. Các phép nhân trung gian có thể gây tràn số khi sử dụng int
 * hoặc long long.
 * Usage: bool left = sideOf(p1,p2,q)==1;
 * Status: Đã kiểm thử
 */
#pragma once

#include "Point.h"

template <class P> int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template <class P> int sideOf(P s, P e, P p, double eps) {
	auto a = (e - s).cross(p - s);
	double l = (e - s).dist() * eps;
	return (a > l) - (a < -l);
}
