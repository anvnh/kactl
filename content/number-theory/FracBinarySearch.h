/**
 * Author: Lucian Bicsi, Simon Lindholm
 * Date: 2017-10-31
 * License: CC0
 * Description: Cho trước hàm $f$ và giới hạn $N$, tìm phân số nhỏ nhất
 *  $p/q \in [0, 1]$ sao cho $f(p/q)$ đúng, với $p, q \le N$.
 * Bạn có thể cho hàm $f$ ném exception nếu tìm được nghiệm chính xác,
 *  khi đó có thể bỏ giới hạn $N$.
 * Usage: fracBS([](Frac f) { return f.p>=3*f.q; }, 10); // {1,3}
 * Time: $O(\log N)$
 * Status: Đã stress-test với $n \le 300$
 */

struct Frac {
	ll p, q;
};
template <class F> Frac fracBS(F f, ll N) {
	bool dir = 1, A = 1, B = 1;
	Frac lo{0, 1}, hi{1, 1}; // Đặt hi = 1/0 để tìm kiếm trên khoảng (0, N]
	if (f(lo))
		return lo;
	assert(f(hi));
	while (A || B) {
		ll adv = 0, step = 1; // Di chuyển hi nếu dir, ngược lại di chuyển lo
		for (int si = 0; step; (step *= 2) >>= si) {
			adv += step;
			Frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
			if (abs(mid.p) > N || mid.q > N || dir == !f(mid)) {
				adv -= step;
				si = 2;
			}
		}
		hi.p += lo.p * adv;
		hi.q += lo.q * adv;
		dir = !dir;
		swap(lo, hi);
		A = B;
		B = !!adv;
	}
	return dir ? hi : lo;
}
