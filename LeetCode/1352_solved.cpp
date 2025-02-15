#include <deque>
class ProductOfNumbers {
private:
	std::deque<int> dq;
public:
	ProductOfNumbers() {}

	void add(int num) {
		for (auto& n : dq)
			n *= num;
		dq.push_back(num);
	}

	int getProduct(int k) {
		return dq[dq.size() - k];
	}
};