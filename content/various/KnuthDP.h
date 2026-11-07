/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: Khi thực hiện DP trên đoạn:
 *  $a[i][j] = \min_{i < k < j}(a[i][k] + a[k][j]) + f(i, j)$,
 *  nếu vị trí k tối ưu nhỏ nhất tăng theo cả i và j,
 *  ta có thể tính DP theo thứ tự độ dài đoạn tăng dần và
 *  chỉ cần tìm k = p[i][j] trong khoảng [p[i][j-1], p[i+1][j]].
 *  Kỹ thuật này được gọi là Knuth DP.
 *  Điều kiện đủ để áp dụng là:
 *  $f(b,c) \le f(a,d)$ và
 *  $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$,
 *  với mọi $a \le b \le c \le d$.
 *  Ngoài ra, có thể tham khảo: LineContainer (chương Data structures),
 *  hàng đợi đơn điệu (Monotone Queue) và tìm kiếm tam phân (Ternary Search).
 * Time: O(N^2)
 */
