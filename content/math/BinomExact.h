/**
 * Author: anvnh
 * Date: 2026-11-02
 * Source: folklore
 * Description: hàm này để tính chính xác $\binom{n}{r}$ (không lấy modulo)
 * bằng cách nhân chia xen kẽ. Sau bước $i$, \texttt{res} $= \binom{n}{i+1}$ nên
 * phép chia luôn chia hết. Kết quả phải vừa trong \texttt{ll}; tích trung gian
 * dùng \texttt{\_\_int128} để không bị tràn. Trả về $0$ nếu $r<0$ hoặc $r>n$.
 * Time: $\mathcal{O}(\min(r, n-r))$
 * Status: chưa test
 */
#pragma once

ll Cexact(ll n, ll r) {
    if (r < 0 || r > n)
        return 0;
    r = min(r, n - r);
    ll res = 1;
    for (ll i = 0; i < r; i++)
        res = (__int128)res * (n - i) / (i + 1);
    return res;
}
