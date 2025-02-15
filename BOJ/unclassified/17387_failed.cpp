
#include <iostream>
#include <math.h>

const double tolerance = 1e-5;
using Point = std::pair<double, double>;

bool cmpTol(double f1, double f2)
{
	if ((f2 - f1) >= -tolerance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool is_not_zero(double val)
{
	if (fabsf(val) <= tolerance)
	{
		return false;
	}
	return true;
}

class Mat2D
{
private:
	Point row1;
	Point row2;
	Point p;
public:
	Mat2D() {}
	Mat2D(const Point& l1s, const Point& l1e, const Point& l2s, const Point& l2e)
	{
		row1.first = l1s.second - l1e.second;	// - delta y
		row1.second = l1e.first - l1s.first;	// + delta x
		p.first = row1.first * l1s.first + row1.second * l1s.second;
		row2.first = l2s.second - l2e.second;
		row2.second = l2e.first - l2s.first;
		p.second = row2.first * l2s.first + row2.second * l2s.second;
	}
	double det() const { return row1.first * row2.second - row1.second * row2.first; }
	void setInverseMatrix(Mat2D* inv) const
	{
		double d = this->det();
		inv->row1.first = this->row2.second / d;
		inv->row2.second = this->row1.first / d;
		inv->row1.second = - this->row1.second / d;
		inv->row2.first = - this->row2.first/ d;
		return;
	}
	Point solve() const
	{
		Point result;
		Mat2D *pinv = new Mat2D();
		setInverseMatrix(pinv);
		result.first = p.first * pinv->row1.first + p.second * pinv->row1.second;
		result.second = p.first * pinv->row2.first + p.second * pinv->row2.second;
		delete pinv;
		return result;
	}
	bool is_overlap(const Point& l1s, const Point& l1e, const Point& l2s, const Point& l2e)
	{
		double l1_low_x = std::min(l1s.first, l1e.first);
		double l1_up_x = std::max(l1s.first, l1e.first);
		double l1_low_y = std::min(l1s.second, l1e.second);
		double l1_up_y = std::max(l1s.second, l1e.second);
		return !(is_not_zero(row1.first * l2s.first + row1.second * l2s.second - p.first)
			&& is_not_zero(row1.first * l2e.first + row1.second * l2e.second - p.first)) // 일치 여부
			&& ((cmpTol(l1_low_x, l2s.first)	// intersection check
				&& cmpTol(l2s.first, l1_up_x)
				&& cmpTol(l1_low_y, l2s.second)
				&& cmpTol(l2s.second, l1_up_y))
				|| (cmpTol(l1_low_x, l2e.first)
					&& cmpTol(l2e.first, l1_up_x)
					&& cmpTol(l1_low_y, l2e.second)
					&& cmpTol(l2e.second, l1_up_y)));
	}
};

bool is_cross(const Point& sol, const Point& l1s, const Point& l1e, const Point& l2s, const Point& l2e)
{
	double low_x = std::max(std::min(l1s.first, l1e.first), std::min(l2s.first, l2e.first));
	double low_y = std::max(std::min(l1s.second, l1e.second), std::min(l2s.second, l2e.second));
	double up_x = std::min(std::max(l1s.first, l1e.first), std::max(l2s.first, l2e.first));
	double up_y = std::min(std::max(l1s.second, l1e.second), std::max(l2s.second, l2e.second));
	//std::cout << low_x << ' ' << up_x << ' ' << low_y << ' ' << up_y << '\n';
	return cmpTol(low_x, sol.first) && cmpTol(sol.first, up_x) && cmpTol(low_y, sol.second) && cmpTol(sol.second, up_y);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Point points[5];
	for (int i = 1; i <= 4; ++i)
	{
		std::cin >> points[i].first >> points[i].second;
	}
	Mat2D System(points[1], points[2], points[3], points[4]);
	if (System.det() == 0)	// parallel
	{
		if (System.is_overlap(points[1], points[2], points[3], points[4]))	// same
			std::cout << 1;
		else    // not same
			std::cout << 0;
		return 0;
	}
	points[0] = System.solve();
	//std::cout << points[0].first << ' ' << points[0].second << '\n';
	if (is_cross(points[0], points[1], points[2], points[3], points[4]))
		std::cout << 1;
	else
		std::cout << 0;
	return 0;
}