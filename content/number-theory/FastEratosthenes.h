/**
 * Author: Jakob Kogler, chilli, pajenegod
 * Date: 2020-04-12
 * License: CC0
 * Description: Sàng nguyên tố, dùng để tìm tất cả các số nguyên tố nhỏ hơn LIM.
 * Time: LIM=1e9 $\approx$ 1.5s
 * Status: Đã kiểm thử áp lực (stress-test)
 * Details: Mặc dù có độ phức tạp $O(n\log\log n)$, sàng phân đoạn vẫn nhanh hơn
 *  các phương pháp khác, bao gồm sàng bitset và sàng tuyến tính.
 *  Nguyên nhân chủ yếu là do mức sử dụng bộ nhớ thấp, giúp giảm cache miss.
 *  Cách cài đặt này bỏ qua các số chẵn.
 *
 * Có thể tìm thấy kết quả benchmark tại:
 * https://ideone.com/e7TbX4
 *
 * Dòng `for (int i=idx; i<S+L; idx = (i+=p))` được viết có chủ đích
 * như vậy nhằm tối ưu hiệu năng.
 * Xem thêm:
 * https://github.com/kth-competitive-programming/kactl/pull/166#discussion_r408354338
 */
#pragma once

const int LIM = 1e6;
bitset<LIM> isPrime;
vi eratosthenes() {
	const int S = (int)round(sqrt(LIM)), R = LIM / 2;
	vi pr = {2}, sieve(S + 1);
	pr.reserve(int(LIM / log(LIM) * 1.1));
	vector<pii> cp;
	for (int i = 3; i <= S; i += 2)
		if (!sieve[i]) {
			cp.push_back({i, i * i / 2});
			for (int j = i * i; j <= S; j += 2 * i)
				sieve[j] = 1;
		}
	for (int L = 1; L <= R; L += S) {
		array<bool, S> block{};
		for (auto &[p, idx] : cp)
			for (int i = idx; i < S + L; idx = (i += p))
				block[i - L] = 1;
		rep(i, 0, min(S, R - L)) if (!block[i]) pr.push_back((L + i) * 2 + 1);
	}
	for (int i : pr)
		isPrime[i] = 1;
	return pr;
}
