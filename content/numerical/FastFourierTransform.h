/**
 * Author: Ludo Pulles, chilli, Simon Lindholm
 * Date: 2019-01-09
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (rất đáng đọc)
 * Accuracy bound from http://www.daemonology.net/papers/fft.pdf
 * Description: fft(a) tính $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$
 * với mọi $k$. N phải là lũy thừa của 2. Ứng dụng hữu ích: tính tích chập
 * (convolution):
 *  \texttt{conv(a, b) = c}, trong đó $c[x] = \sum a[i]b[x-i]$.
 *  Để tính tích chập của các số phức hoặc của nhiều hơn hai vector:
 *  thực hiện FFT, nhân từng phần tử tương ứng, chia cho n,
 *  đảo ngược đoạn [start+1, end), rồi thực hiện FFT lần nữa.
 *  Phép làm tròn đảm bảo chính xác nếu
 *  $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$
 *  (trong thực tế có thể lên đến $10^{16}$; cao hơn với dữ liệu ngẫu nhiên).
 *  Nếu không thỏa mãn, hãy dùng NTT/FFTMod.
 * Time: O(N \log N) với $N = |A|+|B|$ ($\tilde 1s$ khi $N=2^{22}$)
 * Status: đã kiểm thử ở mức tương đối
 */
#pragma once

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C> &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1); // (^ 10% nhanh hơn nếu dùng double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n);
		rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		rep(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
	}
	vi rev(n);
	rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k)
			rep(j, 0, k) {
				// C z = rt[j+k] * a[i+j+k]; // (nhanh hơn 25% nếu tự viết phép
				// nhân) include-line
				auto x = (double *)&rt[j + k],
					 y = (double *)&a[i + j + k]; /// exclude-line
				C z(x[0] * y[0] - x[1] * y[1],
					x[0] * y[1] + x[1] * y[0]); /// exclude-line
				a[i + j + k] = a[i + j] - z;
				a[i + j] += z;
			}
}
vd conv(const vd &a, const vd &b) {
	if (a.empty() || b.empty())
		return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	rep(i, 0, sz(b)) in[i].imag(b[i]);
	fft(in);
	for (C &x : in)
		x *= x;
	rep(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	rep(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}
