/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-17
 * License: CC0
 * Source: Numeriska algoritmer med matlab, Gerd Eriksson, NADA, KTH
 * Description:
 * Tìm vị trí cực tiểu của hàm f trên đoạn [a, b], với giả thiết f là hàm đơn
 * cực (unimodal) trên đoạn này, tức là chỉ có một điểm cực tiểu địa phương
 * và không có điểm cực đại địa phương.
 * Sai số tối đa của kết quả là eps. Có thể sử dụng tương tự để tìm cực đại
 * bằng cách thay đổi một điều kiện nhỏ trong code.
 * Xem TernarySearch.h trong chương Various để biết phiên bản tìm kiếm
 * trên miền rời rạc.
 * Usage:
 * double func(double x) { return 4+x+.3*x*x; }
 * double xmin = gss(-1000,1000,func);
 * Time: O(log((b-a) / eps))
 * Status: tested
 */
#pragma once

/// Giá trị r cần đủ chính xác, nếu không ta không thể đảm bảo bất đẳng thức
/// a < x1 < x2 < b luôn được duy trì.
double gss(double a, double b, double (*f)(double)) {
	double r = (sqrt(5) - 1) / 2, eps = 1e-7;
	double x1 = b - r * (b - a), x2 = a + r * (b - a);
	double f1 = f(x1), f2 = f(x2);
	while (b - a > eps)
		if (f1 < f2) { // đổi thành > nếu muốn tìm cực đại
			b = x2;
			x2 = x1;
			f2 = f1;
			x1 = b - r * (b - a);
			f1 = f(x1);
		} else {
			a = x1;
			x1 = x2;
			f1 = f2;
			x2 = a + r * (b - a);
			f2 = f(x2);
		}
	return a;
}
