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

	Type get_gcd(Type a, Type b) const {
		while (a != b) {
			if (a > b) 
				a = a - b;
			else 
				b = b - a;
		}
		return a;	
	}

	void initialize_ST() {
		int n = std::log2(T.size()); 
		n++;
	        ST = std::vector<std::vector<Type>>(n);
                ST[0] = T;
                for (int k = 1; k < ST.size(); k++) {
                        ST[k] = std::vector<Type>(ST[k-1].size()-(1 << (k-1)));
                        for (int i = 0; i < ST[k].size(); i++) {
                                ST[k][i] = get_gcd(ST[k-1][i], ST[k-1][i+(1 << (k-1))]);
                        }
                }
	}

public:
	RMQ(std::vector<Type> &_T) {
		T = _T;
		initialize_ST();
	}
	
	Type find_gcd(int i, int j) const {
		i--;
		j--;
		int k = std::log2(j-i+1);
		Type ans = get_gcd(ST[k][i], ST[k][j-(1 << k)+1]);
		return ans;
	}
};

int main() {
	int n = 0;
	std::cin >> n;
	std::vector<int> T(n);
	for (int i = 0; i < n; i++) {
		std::cin >> T[i];
	}
	RMQ<int> rmq(T);
	int k = 0;
	std::cin >> k;
	std::vector<int> ans(k);
	for (int i = 0; i < k; i++) {
		int l = 0, r = 0;
		std::cin >> l >> r;
		ans[i] = rmq.find_gcd(l, r);
	}
	for (int i = 0; i < k; i++) {
		std::cout << ans[i] << std::endl;
	}
	return 0;
}

