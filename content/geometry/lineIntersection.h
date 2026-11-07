/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-05-05
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\\
\begin{minipage}{75mm}
Nếu hai đường thẳng đi qua $s_1,e_1$ và $s_2,e_2$ có giao điểm duy nhất, trả về
$\{1,\text{điểm giao}\}$. Nếu không có giao điểm, trả về $\{0,(0,0)\}$. Nếu có
vô số giao điểm (hai đường thẳng trùng nhau), trả về $\{-1,(0,0)\}$. Nếu P là
Point<ll> và giao điểm không có tọa độ nguyên, kết quả trả về sẽ không chính
xác. Các phép tính trung gian sử dụng tích của ba tọa độ, cần chú ý tràn số khi
dùng int hoặc ll.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
\end{minipage}
 * Usage:
 *  auto res = lineInter(s1,e1,s2,e2);
 *  if (res.first == 1)
 *      cout << "intersection point at " << res.second << endl;
 * Status: Đã kiểm thử ngẫu nhiên cường độ cao và kiểm thử thông qua các bài
toán nửa mặt phẳng
 */
#pragma once

#include "Point.h"

template <class P> pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}
