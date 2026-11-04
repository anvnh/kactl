/**
 * Author: chilli
 * Date: 2019-04-25
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
 * Description: FFT với độ chính xác cao hơn, có thể dùng để tính tích chập
 * modulo một số nguyên bất kỳ, miễn là $N\log_2N\cdot \text{mod} < 8.6 \cdot
 * 10^{14}$ (trong thực tế có thể lên đến $10^{16}$ hoặc cao hơn). Các phần tử
 * đầu vào phải thuộc đoạn $[0, \text{mod})$.
 * Time: O(N \log N), với $N = |A|+|B|$ (chậm gấp đôi NTT hoặc FFT thông thường)
 * Status: đã kiểm thử áp lực
 **/
#pragma once

#include "FastFourierTransform.h"

typedef vector<ll> vl;
template <int M> vl convMod(const vl &a, const vl &b) {
	if (a.empty() || b.empty())
		return {};
	vl res(sz(a) + sz(b) - 1);
	int B = 32 - __builtin_clz(sz(res)), n = 1 << B, cut = int(sqrt(M));
	vector<C> L(n), R(n), outs(n), outl(n);
	rep(i, 0, sz(a)) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
	rep(i, 0, sz(b)) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
	fft(L), fft(R);
	rep(i, 0, n) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	rep(i, 0, sz(res)) {
		ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
		ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}
