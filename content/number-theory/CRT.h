/**
 * Author: Simon Lindholm
 * Date: 2019-05-22
 * License: CC0
 * Description: Định lý số dư Trung Hoa (Chinese Remainder Theorem).
 * \texttt{crt(a, m, b, n)} tính $x$ sao cho $x\equiv a \pmod m$, $x\equiv b
 * \pmod n$. Nếu $|a| < m$ và $|b| < n$, $x$ sẽ thỏa $0 \le x < \text{lcm}(m,
 * n)$. Giả sử $mn < 2^{62}$.
 * Time: $\log(n)$
 * Status: Works
 */
#pragma once
#include <cassert>

#include "euclid.h"

ll crt(ll a, ll m, ll b, ll n) {
	if (n > m)
		swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m * n / g : x;
}
