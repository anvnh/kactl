/**
 * Author: chilli, c1729, Simon Lindholm
 * Date: 2019-03-28
 * License: CC0
 * Source: Wikipedia, https://miller-rabin.appspot.com/
 * Description: Thuật toán Miller-Rabin xác định để kiểm tra tính nguyên tố.
 *  Đảm bảo hoạt động chính xác với các số không vượt quá $7 \cdot 10^{18}$;
 *  với các số lớn hơn, hãy sử dụng Python và mở rộng tập cơ sở A bằng
 *  các giá trị được chọn ngẫu nhiên.
 * Time: Gấp 7 lần độ phức tạp của phép tính $a^b \bmod c$.
 * Status: Đã kiểm thử áp lực (stress-test)
 */
#pragma once

#include "ModMulLL.h"

bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1)
		return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
		s = __builtin_ctzll(n - 1), d = n >> s;
	for (ull a : A) { // ^ count trailing zeroes
		ull p = modpow(a % n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n - 1 && i != s)
			return 0;
	}
	return 1;
}
