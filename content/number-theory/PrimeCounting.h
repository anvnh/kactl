/**
 * Author: Anvnh
 * Date: 2026-11-05
 * License: CC0
 * Source: Lucy_Hedgehog (Project Euler forum, bài 10)
 * Description: Đếm số nguyên tố $\le n$, tức $\pi(n)$.
 *  Chỉ cần quan tâm các giá trị dạng $\lfloor n / i \rfloor$ (có $2\sqrt{n}$
 * giá trị). Gọi $S(v, p)$ là số $x \in [2, v]$ mà $x$ là nguyên tố hoặc có ước
 * nguyên tố nhỏ nhất $> p$. Khi đó $S(v, p) = S(v, p-1) - (S(v/p, p-1) - S(p-1,
 * p-1))$ nếu $p$ nguyên tố và $p^2 \le v$, ngược lại giữ nguyên. Bắt đầu từ
 * $S(v, 1) = v - 1$. lo[i] lưu $S(i, \cdot)$, hi[i] lưu $S(\lfloor n/i \rfloor,
 * \cdot)$. Chỉ cần đổi hàm khởi tạo và phép trừ là đếm được các hàm khác (ví dụ
 * tổng các số nguyên tố, với hàm nhân tính hoàn toàn).
 * Usage: ll c = primeCount(1e10);
 * Time: O(n^{3/4}), bộ nhớ $O(\sqrt{n})$
 * Status: chưa test
 */
#pragma once

ll primeCount(ll n) {
	if (n < 2)
		return 0;
	ll r = sqrtl(n);
	while (r * r > n)
		r--;
	while ((r + 1) * (r + 1) <= n)
		r++;
	vector<ll> lo(r + 1), hi(r + 1);
	rep(i, 1, r + 1) lo[i] = i - 1, hi[i] = n / i - 1;
	for (ll p = 2; p <= r; p++) {
		if (lo[p] == lo[p - 1])
			continue; // p không nguyên tố
		ll pc = lo[p - 1], p2 = p * p;
		ll end = min(r, n / p2);
		for (ll i = 1; i <= end; i++) {
			ll d = i * p;
			hi[i] -= (d <= r ? hi[d] : lo[n / d]) - pc;
		}
		for (ll i = r; i >= p2; i--)
			lo[i] -= lo[i / p] - pc;
	}
	return hi[1];
}
