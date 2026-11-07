/**
 * Author: Anvnh
 * Date: 2026-11-05
 * License: CC0
 * Source: folklore
 * Description: Sàng tuyến tính: mỗi hợp số $i \cdot p$ chỉ bị gạch đúng một
 * lần, bởi ước nguyên tố nhỏ nhất của nó. Tính cho mọi $i \le$ LIM: lp[i] = ước
 * nguyên tố nhỏ nhất, phi[i] = hàm Euler, mu[i] = hàm Mobius, và pr = danh sách
 * các số nguyên tố tăng dần. Với LIM $= 10^7$ ba mảng int tốn khoảng 120MB, bỏ
 * bớt mảng không cần dùng.
 *
 *  Hàm Euler: $\phi(n)$ = số nguyên dương không vượt quá $n$ và nguyên tố cùng
 * nhau với $n$.
 *  $\phi(1) = 1$, $\phi(p^k) = (p-1)p^{k-1}$ với $p$ nguyên tố, và nhân tính:
 *  $\gcd(m,n)=1 \Rightarrow \phi(mn) = \phi(m)\phi(n)$.
 *  Nếu $n = p_1^{k_1} \cdots p_r^{k_r}$ thì $\phi(n) = n \prod_{p \mid n} (1 -
 * 1/p)$.
 *  $\sum_{d \mid n} \phi(d) = n$. $\sum_{1 \le k \le n, \gcd(k,n)=1} k =
 * n\phi(n)/2$ với $n > 1$. Định lý Euler: $\gcd(a,n)=1 \Rightarrow a^{\phi(n)}
 * \equiv 1 \pmod n$. Định lý nhỏ Fermat: $p$ nguyên tố, $p \nmid a \Rightarrow
 * a^{p-1} \equiv 1 \pmod p$.
 *
 *  Hàm Mobius: $\mu(n) = 0$ nếu $n$ có thừa số chính phương, ngược lại
 *  $\mu(n) = (-1)^k$ với $k$ là số ước nguyên tố phân biệt của $n$.
 *  $\sum_{d \mid n} \mu(d) = [n = 1]$.
 * Usage: linearSieve(); gọi một lần, sau đó dùng lp, phi, mu, pr với $n \le$
 * LIM. Xem ví dụ ở cuối file.
 * Time: O(LIM)
 * Status: đã test
 */
#pragma once

const int LIM = 1e6;
int lp[LIM + 1], phi[LIM + 1], mu[LIM + 1];
vi pr;
void linearSieve() {
	phi[1] = mu[1] = 1;
	rep(i, 2, LIM + 1) {
		if (!lp[i])
			lp[i] = i, pr.push_back(i), phi[i] = i - 1, mu[i] = -1;
		for (int p : pr) {
			if (p > lp[i] || (ll)i * p > LIM)
				break;
			lp[i * p] = p;
			if (p == lp[i])
				phi[i * p] = phi[i] * p, mu[i * p] = 0;
			else
				phi[i * p] = phi[i] * (p - 1), mu[i * p] = -mu[i];
		}
	}
}
// Các thừa số nguyên tố của n (có lặp), O(log n)
for (int x = n; x > 1; x /= lp[x])
	cout << lp[x] << ' ';
// Phân tích dạng p^e, và số ước tau(n) = tích (e+1)
int tau = 1;
for (int x = n; x > 1;) {
	int p = lp[x], e = 0;
	while (x % p == 0)
		x /= p, e++;
	tau *= e + 1; // n có thừa số p^e
}
// Kiểm tra nguyên tố: n >= 2 && lp[n] == n
// Tổng tiền tố phi (dùng ll vì tổng vượt int),mu tương tự
vector<ll> sp(LIM + 1);
rep(i, 1, LIM + 1) sp[i] = sp[i - 1] + phi[i];
// phi của một số n lớn (n <= LIM*LIM, ví dụ LIM = 1e6 thì n <= 1e12):
ll phiOne(ll n) {
	ll r = n;
	for (int p : pr) {
		if ((ll)p * p > n)
			break;
		if (n % p == 0) {
			while (n % p == 0)
				n /= p;
			r -= r / p;
		}
	}
	if (n > 1)
		r -= r / n;
	return r;
}
// Nghịch đảo modulo m khi biết phi(m): a^(-1) = a^(phi(m)-1) mod m, với gcd(a,
// m) = 1.
