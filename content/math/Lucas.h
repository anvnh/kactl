/**
 * Author: anvnh
 * Date: 2026-11-02
 * Source: https://en.wikipedia.org/wiki/Lucas%27s_theorem
 * Description: hàm này để tính $\binom{n}{r} \bmod p$ với $p$ là số nguyên tố
 * nhỏ ($p \le N$) còn $n, r$ rất lớn (tới $10^{18}$). Theo định lý Lucas,
 * $\binom{n}{r} \equiv \prod_i \binom{n_i}{r_i} \pmod p$ với $n_i, r_i$ là các
 * chữ số của $n, r$ trong hệ cơ số $p$ (bằng $0$ nếu có $n_i < r_i$).
 * Cần BinomMod.h: đặt \texttt{MOD} $= p$ rồi gọi \texttt{init()} trước.
 * Usage: MOD = 99991; init(); lucas(1e18, 12345);
 * Time: $\mathcal{O}(p + \log_p n)$
 */
#pragma once

ll lucas(ll n, ll r) {
    if (r < 0 || r > n)
        return 0;
    ll res = 1;
    for (; n || r; n /= MOD, r /= MOD)
        res = res * C(n % MOD, r % MOD) % MOD;
    return res;
}
