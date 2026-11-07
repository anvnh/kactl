/**
 * Author: Simon Lindholm
 * Date: 2015-05-13
 * Source: Wikipedia
 * Description: Sau khi chạy luồng cực đại (max-flow), phía trái của lát cắt
 * nhỏ nhất từ $s$ đến $t$ gồm tất cả các đỉnh có thể đi tới được từ $s$, chỉ
 * đi qua các cạnh còn dung lượng dư (residual capacity) dương. Trong Dinic và
 * PushRelabel đã có sẵn hàm \texttt{leftOfMinCut(a)} để kiểm tra đỉnh $a$ có
 * thuộc phía trái hay không.
 * Status: works
 */
