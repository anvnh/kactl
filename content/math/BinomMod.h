/**
 * Author: anvnh
 * Date: 2026-11-02
 * Source: folklore
 * Description: hàm này để tính $\binom{n}{r} \bmod p$ với $p$ nguyên tố và
 * $n \le \min(N-1, p-1)$. \texttt{init()} tiền xử lý giai thừa và nghịch đảo
 * giai thừa (đặt \texttt{MOD} trước khi gọi), sau đó mỗi truy vấn \texttt{C(n,
 * r)} mất $\mathcal{O}(1)$. Nếu $n \ge p$ thì dùng \texttt{lucas} trong
 * Lucas.h.
 * Usage: MOD = 1000000007; init(); C(10, 3);
 * Time: $\mathcal{O}(N)$, mỗi truy vấn $\mathcal{O}(1)$
 * Status: chưa test
 */
#pragma once

const int N = 1000005;
ll MOD = 1000000007, fact[N], ifact[N];
ll pw(ll a, ll e) {
    ll r = 1;
    a %= MOD;
    for (; e; e >>= 1, a = a * a % MOD)
        if (e & 1)
            r = r * a % MOD;
    return r;
}
void init() {
    int L = min<ll>(N - 1, MOD - 1);
    fact[0] = 1;
    for (int i = 1; i <= L; i++)
        fact[i] = fact[i - 1] * i % MOD;
    ifact[L] = pw(fact[L], MOD - 2);
    for (int i = L; i; i--)
        ifact[i - 1] = ifact[i] * i % MOD;
}
ll C(ll n, ll r) {
    if (r < 0 || r > n)
        return 0;
    return fact[n] * ifact[r] % MOD * ifact[n - r] % MOD;
}
