/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Kiểm tra điểm $p$ có nằm trên đoạn thẳng $se$ hay không.
 *  Với Point<double>, nên dùng \texttt{(segDist(s,e,p)<=epsilon)} thay thế.
 * Status:
 */
#pragma once

#include "Point.h"

template <class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
