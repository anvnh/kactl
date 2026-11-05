/**
 * Author: Bjorn Martinsson
 * Date: 2020-06-03
 * License: CC0
 * Source: mã nguồn tự viết
 * Description: Trả về giá trị $x > 0$ nhỏ nhất thỏa mãn
 *  $a^x \equiv b \pmod m$, hoặc trả về $-1$ nếu không tồn tại $x$ như vậy.
 *  Có thể sử dụng modLog(a, 1, m) để tính cấp của $a$ modulo $m$.
 * Time: $O(\sqrt m)$
 * Status: Đã kiểm thử với mọi $0 \le a,x < 500$ và $0 < m < 500$.
 *
 * Details: Thuật toán sử dụng phương pháp baby-step giant-step (BSGS)
 *  để tìm $(i,j)$ sao cho $a^{n \cdot i} \equiv b \cdot a^j \pmod m$,
 *  trong đó $n > \sqrt m$ và $0 < i,j \le n$.
 *  Nếu $a$ và $m$ nguyên tố cùng nhau thì $a^j$ có nghịch đảo modulo,
 *  do đó ta có thể suy ra $a^{i \cdot n-j} \equiv b \pmod m$.
 *
 *  Tuy nhiên, cách cài đặt BSGS cụ thể này vẫn hoạt động ngay cả khi
 *  không giả sử $a$ và $m$ nguyên tố cùng nhau, nhờ ý tưởng sau:
 *
 *  Giả sử $p^x$ là một ước nguyên tố của $m$. Khi đó có 3 trường hợp:
 *   1. $b$ chia hết cho $p^x$.
 *   2. $b$ chỉ chia hết cho một lũy thừa $p^y$, với $0 < y < x$.
 *   3. $b$ không chia hết cho $p$.
 *
 *  Điều quan trọng cần lưu ý là ở trường hợp 2, nếu modLog(a,b,m) tồn tại
 *  thì giá trị của nó không thể lớn hơn $\sqrt m$
 *  (chính xác hơn, nó không thể lớn hơn hoặc bằng $\log_2(m)$).
 *  Vì vậy, sau khi đã kiểm tra tất cả số mũ của $a$ không vượt quá
 *  $\sqrt m$, ta có thể loại bỏ trường hợp 2. Đây là trường hợp duy nhất
 *  cần xử lý phức tạp.
 *
 *  Do đó, phần sửa đổi để hỗ trợ cả trường hợp $a$ và $m$ không nguyên tố
 *  cùng nhau bao gồm: kiểm tra tất cả số mũ của $a$ không vượt quá $n$,
 *  sau đó xử lý các trường hợp còn lại một cách đơn giản bằng cách kiểm tra
 *  $\gcd(a^n,m) = \gcd(b,m)$.
 */
#pragma once

ll modLog(ll a, ll b, ll m) {
	ll n = (ll)sqrt(m) + 1, e = 1, f = 1, j = 1;
	unordered_map<ll, ll> A;
	while (j <= n && (e = f = e * a % m) != b % m)
		A[e * b % m] = j++;
	if (e == b % m)
		return j;
	if (__gcd(m, e) == __gcd(m, b))
		rep(i, 2, n + 2) if (A.count(e = e * f % m)) return n * i - A[e];
	return -1;
}
