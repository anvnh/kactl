/**
 * Author: anvnh
 * Date: 2026-11-02
 * Source: folklore
 * Description: hàm này để tìm xâu (hoán vị có lặp) thứ $k$ theo thứ tự từ điển,
 * $k$ đánh số từ $1$. \texttt{a[i]} là số lần xuất hiện của ký tự
 * \texttt{'a'+i}. Trả về xâu rỗng nếu $k$ lớn hơn tổng số hoán vị. Thuật toán
 * tham lam: ở mỗi vị trí thử ký tự $c$ tăng dần, \texttt{cnt} là số hoán vị của
 * phần còn lại $\binom{n-1}{a_1,\dots,a_c-1,\dots,a_m}$; nếu $k \le$
 * \texttt{cnt} thì chốt $c$, ngược lại $k \mathrel{-}=$ \texttt{cnt}. Mọi phép
 * cộng/nhân bị chặn trên bởi \texttt{INF} để không tràn số (không cần BigInt).
 * Gọi \texttt{initPascal()} một lần ở đầu. Usage: initPascal(); kth({2, 1, 1},
 * 5); // các ký tự a,a,b,c: aabc, aacb, abac, abca, acab => "acab" Time:
 * $\mathcal{O}(M^2)$ khởi tạo, $\mathcal{O}(n \cdot m^2)$ mỗi truy vấn Status:
 * chưa test
 */
#pragma once

const ll INF = 2e18;
const int M = 2005; // độ dài xâu tối đa
ll Cs[M][M];
void initPascal() {
    for (int i = 0; i < M; i++) {
        Cs[i][0] = 1;
        for (int j = 1; j <= i; j++)
            Cs[i][j] = min(INF, Cs[i - 1][j - 1] + Cs[i - 1][j]);
    }
}
ll mulSat(ll a, ll b) { return (a && b > INF / a) ? INF : a * b; }
ll multinomial(const vector<int> &a, int n) {
    ll res = 1;
    for (int x : a) {
        res = mulSat(res, Cs[n][x]);
        n -= x;
    }
    return res;
}
string kth(vector<int> a, ll k) {
    int n = accumulate(a.begin(), a.end(), 0);
    if (multinomial(a, n) < k)
        return "";
    string s;
    for (int pos = 0; pos < n; pos++)
        for (int c = 0; c < (int)a.size(); c++)
            if (a[c]) {
                a[c]--;
                ll cnt = multinomial(a, n - pos - 1);
                if (k <= cnt) {
                    s += char('a' + c);
                    break;
                }
                k -= cnt;
                a[c]++;
            }
    return s;
}
