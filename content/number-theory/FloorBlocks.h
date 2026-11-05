/**
 * Author: Anvnh
 * Date: 2026-10-23
 * License: CC0
 * Source: folklore
 * Description: Duyệt qua các block cực đại $[l, r]$ mà trên đó
 *  $\lfloor n / i \rfloor$ không đổi. Có tối đa $2\sqrt{n}$ block.
 *  Dùng cho các tổng dạng $\sum_{i=1}^{n} f(i) \cdot \lfloor n / i \rfloor$,
 *  với $f$ có tổng tiền tố tính được nhanh (ví dụ $f(i) = i$).
 *  Yêu cầu $n \ge 1$.
 * Usage: Đây là snippet, đặt bên trong hàm.
 *  ll n = ...;
 *  for (ll l = 1, r; l <= n; l = r + 1) {
 *    r = n / (n / l);
 *    // với mọi i trong [l, r]: n / i == n / l
 *    // ví dụ: ans += (n / l) * (sum(r) - sum(l - 1));
 *  }
 * Time: O(\sqrt{n})
 * Status: vòng lặp chuẩn, chưa test riêng
 */
#pragma once

for (ll l = 1, r; l <= n; l = r + 1) {
	r = n / (n / l);
	// for every i in [l, r]: n / i == n / l
}
