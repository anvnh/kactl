/**
 * Author: chilli
 * Date: 2019-04-16
 * License: CC0
 * Source: dựa trên FFT của KACTL
 * Description: ntt(a) tính $\hat f(k) = \sum_x a[x] g^{xk}$ với mọi $k$,
 *  trong đó $g=\text{root}^{(mod-1)/N}$.
 *  N phải là lũy thừa của 2.
 *  Hữu ích để tính tích chập modulo các số nguyên tố đặc biệt có dạng $2^a
 * b+1$, trong đó kích thước kết quả tích chập không vượt quá $2^a$. Với modulo
 * bất kỳ, xem FFTMod.
 *  \texttt{conv(a, b) = c}, trong đó $c[x] = \sum a[i]b[x-i]$.
 *  Nếu tự tính tích chập: thực hiện NTT trên các đầu vào, nhân từng phần tử
 *  tương ứng, chia cho n, đảo ngược đoạn [start+1, end), rồi thực hiện NTT lần
 * nữa. Các phần tử đầu vào phải thuộc $[0, \text{mod})$.
 * Time: O(N \log N)
 * Status: đã kiểm thử áp lực (stress-test)
 */
#pragma once
#include "../number-theory/ModPow.h"
const ll mod = (119 << 23) + 1, root = 62; // = 998244353
// Với p < 2^30 còn có thể dùng, chẳng hạn: 5 << 25, 7 << 26, 479 << 21
// và 483 << 21 (hai giá trị cuối lớn hơn 10^9).
typedef vector<ll> vl;
void ntt(vl &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, modpow(root, mod >> s)};
		rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	vi rev(n);
	rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k)
			rep(j, 0, k) {
				ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
				a[i + j + k] = ai - z + (z > ai ? mod : 0);
				ai += (ai + z >= mod ? z - mod : z);
			}
}
vl conv(const vl &a, const vl &b) {
	if (a.empty() || b.empty())
		return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
	ll inv = modpow(n, mod - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	rep(i, 0, n) out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}
