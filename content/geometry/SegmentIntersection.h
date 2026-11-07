/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-27
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\\
\begin{minipage}{75mm}
Tìm giao điểm của hai đoạn thẳng $s_1e_1$ và $s_2e_2$.
Nếu hai đoạn thẳng có đúng một giao điểm, trả về vector chứa điểm giao đó.
Nếu không có giao điểm, trả về vector rỗng.
Nếu có vô số giao điểm, trả về vector gồm 2 phần tử là hai đầu mút của đoạn
thẳng chung. Nếu P là Point<ll> và giao điểm không có tọa độ nguyên, kết quả trả
về sẽ không chính xác. Các phép tính trung gian sử dụng tích của ba tọa độ, cần
chú ý tràn số khi dùng int hoặc long long.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
\end{minipage}
 * Usage:
 *  vector<P> inter = segInter(s1,e1,s2,e2);
 *  if (sz(inter)==1)
 *    cout << "segments intersect at " << inter[0] << endl;
 * Status: Đã kiểm thử ngẫu nhiên cường độ cao, kiểm thử trên Kattis:
intersection
 */
#pragma once

#include "OnSegment.h"
#include "Point.h"

template <class P> vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c),
		 od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if (onSegment(c, d, a))
		s.insert(a);
	if (onSegment(c, d, b))
		s.insert(b);
	if (onSegment(a, b, c))
		s.insert(c);
	if (onSegment(a, b, d))
		s.insert(d);
	return {all(s)};
}
