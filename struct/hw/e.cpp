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
	std::vector<std::vector<int>> CT; // count

	void initialize_ST() {
		int n = std::log2(T.size()); 
		n++;
	        ST = std::vector<std::vector<Type>>(n);
		CT = std::vector<std::vector<int>>(n);
                ST[0] = T;
		CT[0] = std::vector<int>(T.size(), 1);
                for (int k = 1; k < ST.size(); k++) {
                        ST[k] = std::vector<Type>(ST[k-1].size()-(1 << (k-1)));
			CT[k] = std::vector<int>(ST[k-1].size()-(1 << (k-1)));
                        for (int i = 0; i < ST[k].size(); i++) {
                                ST[k][i] = std::max(ST[k-1][i], ST[k-1][i+(1 << (k-1))]);
				if (ST[k-1][i+(1 << (k-1))] == ST[k-1][i]) {
					CT[k][i] = CT[k-1][i] + CT[k-1][i+(1 << (k-1))];
				} else if (ST[k][i] == ST[k-1][i+(1 << (k-1))]) {
					CT[k][i] = CT[k-1][i+(1 << (k-1))];
				} else if (ST[k][i] == ST[k-1][i]) {
					CT[k][i] = CT[k-1][i];
				}
                        }
                }
	}

	int get_elements_number(Type ans1, int i, int j) const {
		if (i >= j)
			return (i == j && ST[0][i] == ans1) ? 1 : 0;
		int k = std::log2(j-i+1);
		if (ST[k][i] != ST[k][j-(1 << k)+1] || j-(1 << k)+1 <= i+(1 << k)-1) {
			return (ans1 == ST[k][i]) ? CT[k][i] : CT[k][j-(1 << k)+1];
		} else {
			return CT[k][i] + CT[k][j-(1 << k)+1] - get_elements_number(ans1, j-(1 << k)+1, i+(1 << k)-1);
		}
	}

public:
	RMQ(std::vector<Type> &_T) {
		T = _T;
		initialize_ST();
	}
	
	std::pair<Type, int> find_max(int i, int j) const {
		i--;
		j--;
		int k = std::log2(j-i+1);
		Type ans1 = std::max(ST[k][i], ST[k][j-(1 << k)+1]);
		int ans2 = get_elements_number(ans1, i, j);
		return std::make_pair(ans1, ans2);
	}
};

int main() {
	int n = 0;
	std::cin >> n;
	std::vector<long long> T(n);
	for (int i = 0; i < n; i++) {
		std::cin >> T[i];
	}
	RMQ<long long> rmq(T);
	int k = 0;
	std::cin >> k;
	std::vector<std::pair<long long, int>> ans(k);
	for (int i = 0; i < k; i++) {
		int l = 0, r = 0;
		std::cin >> l >> r;
		ans[i] = rmq.find_max(l, r);
	}
	for (int i = 0; i < k; i++) {
		std::cout << ans[i].first << " " << ans[i].second << std::endl;
	}
	return 0;
}

