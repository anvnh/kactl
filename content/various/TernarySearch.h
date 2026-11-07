/**
 * Author: Simon Lindholm
 * Date: 2015-05-12
 * License: CC0
 * Source: own work
 * Description:
 * Tìm chỉ số i nhỏ nhất trong [a, b] sao cho f(i) đạt giá trị lớn nhất,
 *  giả sử f(a) < ... < f(i) >= ... >= f(b).
 * Để đảo ngược phía được phép có dấu bằng trong tính đơn điệu,
 *  đổi dấu < tại (A) thành <= và đảo ngược vòng lặp tại (B).
 * Để tìm giá trị nhỏ nhất của f, đổi dấu < thành >, kể cả tại (B).
 * Usage:
 *  int ind = ternSearch(0,n-1,[](int i){return a[i];});
 * Time: O(\log(b-a))
 * Status: tested
 */
#pragma once
#include <cassert>

template <class F> int ternSearch(int a, int b, F f) {
	assert(a <= b);
	while (b - a >= 5) {
		int mid = (a + b) / 2;
		if (f(mid) < f(mid + 1))
			a = mid; // (A)
		else
			b = mid + 1;
	}
	rep(i, a + 1, b + 1) if (f(a) < f(i)) a = i; // (B)
	return a;
}
