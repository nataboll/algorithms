#include <iostream>
#include <vector>
#include <algorithm>	
#include <cmath>
#include <utility>

template<class Type>
class RMQ {
private:
	std::vector<Type> T;
	std::vector<std::vector<Type>> ST;

	void initialize_ST() {
		int n = std::log2(T.size()); 
		n++;
	        ST = std::vector<std::vector<Type>>(n);
                ST[0] = T;
                for (int k = 1; k < ST.size(); k++) {
                        ST[k] = std::vector<Type>(ST[k-1].size()-(1 << (k-1)));
                        for (int i = 0; i < ST[k].size(); i++) {
                                ST[k][i] = std::min(ST[k-1][i], ST[k-1][i+(1 << (k-1))]);
                        }
                }
	}

	void set_T(int n, int a1) {
		T = std::vector<Type>(n);
		T[0] = a1;
		for (int i = 1; i < n; i++) {
			T[i] = (23 * T[i-1] + 21563) % 16714589;
		}
	}

public:
	RMQ(std::vector<Type> &_T) {
		T = _T;
		initialize_ST();
	}

	RMQ(int n, int a1) {
		set_T(n, a1);
		initialize_ST();
	}
	
	Type find_max(int i, int j) const {
		i--;
		j--;
		int k = std::log2(j-i+1);
		if (k == 0)
			return T[i];

		Type ans = std::min(ST[k][i], ST[k][j-(1 << k)+1]);
		return ans;
	}

	std::vector<Type> get_array() const {
		return T;
	}
};

int main() {
	int n = 0, m = 0, a1 = 0, l = 0, r = 0, ans = 0;
	std::cin >> n >> m >> a1 >> l >> r;
	RMQ<int> rmq(n, a1);

	ans = (l > r) ? rmq.find_max(r, l) : rmq.find_max(l, r);

	for (int i = 2; i < m + 1; i++) {
		l = (17 * l + 751 + ans + 2*(i-1)) % n + 1;
		r = (13 * r + 593 + ans + 5*(i-1)) % n + 1;
		ans = (l > r) ? rmq.find_max(r, l) : rmq.find_max(l, r);
	}
		
	std::cout << l << " " << r << " " << ans << std::endl;
	return 0;
}

