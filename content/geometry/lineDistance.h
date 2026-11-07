/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: Basic math
 * Description:\\
\begin{minipage}{75mm}
Tính khoảng cách có dấu từ điểm $p$ đến đường thẳng đi qua hai điểm $a$ và $b$.
Giá trị dương nếu $p$ nằm bên trái và âm nếu nằm bên phải khi nhìn theo hướng từ
$a$ đến $b$. Nếu $a=b$, kết quả là nan. P được giả định là Point<T> hoặc
Point3D<T>, trong đó T có thể là double hoặc long long. Các phép nhân trung gian
có thể gây tràn số khi sử dụng int hoặc long long. Với Point3D, kết quả luôn
không âm. Khi đó, gọi .dist() trên kết quả của tích có hướng để lấy khoảng cách.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Status: Đã kiểm thử
 */
#pragma once

#include "Point.h"

template <class P> double lineDist(P a, P b, P p) {
	return (double)(b - a).cross(p - a) / (b - a).dist();
}
