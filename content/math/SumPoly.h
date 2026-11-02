/**
 * Author: anvnh
 * Date: 2026-11-02
 * Source: folklore
 * Description: hàm này để tính $\sum_{k=0}^{n} P(k) \binom{n}{k}$ theo modulo
 * MOD, với $n$ rất lớn (tới $10^{18}$) và $P$ có bậc nhỏ. Viết $P(k) = \sum_r
 * c_r (k)_r$ với $(k)_r = k(k-1)\cdots(k-r+1)$ là giai thừa giảm, khi đó tổng
 * bằng
 * $\sum_r c_r (n)_r 2^{n-r}$. Đổi cơ sở: $k^2 = (k)_2 + (k)_1$,
 * $k^3 = (k)_3 + 3(k)_2 + (k)_1$, $k^4 = (k)_4 + 6(k)_3 + 7(k)_2 + (k)_1$.
 * Cần BinomMod.h cho pw và MOD.
 * Usage: sumPoly(n, {0, 1, 1}); // tong k*k*C(n,k)
 * Time: $\mathcal{O}(d \log n)$ với $d$ là bậc của $P$
 * Status: chưa test
 */
#pragma once

ll sumPoly(ll n, const vector<ll> &c) {
    ll res = 0, f = 1; // f = (n)_r mod MOD
    for (int r = 0; r < (int)c.size() && r <= n; r++) {
        res = (res + c[r] % MOD * f % MOD * pw(2, n - r)) % MOD;
        f = f * ((n - r) % MOD) % MOD;
    }
    return res;
}
