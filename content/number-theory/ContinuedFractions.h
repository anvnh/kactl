/**
 * Author: Simon Lindholm
 * Date: 2018-07-15
 * License: CC0
 * Source: Wikipedia
 * Description: Cho trước $N$ và một số thực $x \ge 0$, tìm phân số xấp xỉ
 *  hữu tỉ $p/q$ gần với $x$ nhất, với $p, q \le N$. Kết quả thỏa mãn
 *  $|p/q - x| \le 1/qN$.
 *
 * Với hai phân số hội tụ liên tiếp, ta có:
 *  $p_{k+1}q_k - q_{k+1}p_k = (-1)^k$.
 *  ($p_k/q_k$ luân phiên lớn hơn và nhỏ hơn $x$.)
 *
 * Nếu $x$ là số hữu tỉ, $y$ cuối cùng sẽ tiến tới $\infty$.
 * Nếu $x$ là nghiệm của một đa thức bậc $2$, các hệ số $a$ cuối cùng sẽ
 *  tuần hoàn.
 *
 * Time: $O(\log N)$
 * Status: Đã stress-test với $n \le 300$
 */

typedef double d; // for N ~ 1e7; long double for N ~ 1e9
pair<ll, ll> approximate(d x, ll N) {
	ll LP = 0, LQ = 1, P = 1, Q = 0, inf = LLONG_MAX;
	d y = x;
	for (;;) {
		ll lim = min(P ? (N - LP) / P : inf, Q ? (N - LQ) / Q : inf),
		   a = (ll)floor(y), b = min(a, lim), NP = b * P + LP, NQ = b * Q + LQ;
		if (a > b) {
			// If b > a/2, we have a semi-convergent that gives us a
			// better approximation; if b = a/2, we *may* have one.
			// Return {P, Q} here for a more canonical approximation.
			return (abs(x - (d)NP / (d)NQ) < abs(x - (d)P / (d)Q))
					   ? make_pair(NP, NQ)
					   : make_pair(P, Q);
		}
		if (abs(y = 1 / (y - (d)a)) > 3 * N) {
			return {NP, NQ};
		}
		LP = P;
		P = NP;
		LQ = Q;
		Q = NQ;
	}
}
