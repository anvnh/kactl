/**
 * Author: Anvnh
 * Date: 2026-10-23
 * License: CC0
 * Source:
 * Description: Tính giai thừa, giai thừa nghịch đảo và tổ hợp nCr modulo số
 * nguyên tố M. Gọi initFact() một lần trước khi sử dụng nCr.
 * Time: O(MAXN) tiền xử lý, O(1) cho mỗi truy vấn
 * Status: Đã kiểm thử bằng cách
 * so sánh với tam giác Pascal và số nguyên lớn trong Python
 */
#pragma once

#include "ModInverse.h"

const ll mod = 1000000007;
const int MAXN = 1000001;
ll fact[MAXN], invfact[MAXN];
void initFact() {
	fact[0] = 1;
	rep(i, 1, MAXN) fact[i] = fact[i - 1] * i % mod;
	invfact[MAXN - 1] = modinvPrime(fact[MAXN - 1], mod);
	for (int i = MAXN - 1; i > 0; i--)
		invfact[i - 1] = invfact[i] * i % mod;
}
ll nCr(int n, int r) {
	if (r < 0 || r > n)
		return 0;
	return fact[n] * invfact[r] % mod * invfact[n - r] % mod;
}
