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
	std::vector<std::vector<int>> IT; // index tree

	void initialize_ST() {
		int n = std::log2(T.size()); 
		n++;
	        ST = std::vector<std::vector<Type>>(n);
		IT = std::vector<std::vector<Type>>(n);
                ST[0] = T;
		for (int i = 0; i < IT.size(); i++) {
			IT[0][i] = i;
		}
                for (int k = 1; k < ST.size(); k++) {
                        ST[k] = std::vector<Type>(ST[k-1].size()-(1 << (k-1)));
			IT[k] = std::vector<Type>(IT[k-1].size()-(1 << (k-1)));
                        for (int i = 0; i < ST[k].size(); i++) {
                                ST[k][i] = std::max(ST[k-1][i], ST[k-1][i+(1 << (k-1))]);
				IT[k][i] = (ST[k-1][i] == ST[k][i]) ? i : i+(1 << (k-1)); 
                        }
                }
	}

public:
	RMQ(std::vector<Type> &_T) {
		T = _T;
		initialize_ST();
	}
	
	std::pair<int, Type> find_max(int i, int j) {
		i--;
		j--;
		int k = std::log2(j-i+1);
		if (k == 0)
			return std::make_pair(i+1, T[i]);

		Type ans2 = std::max(ST[k][i], ST[k][j-(1 << k)+1]);
		int ans1 = (ans2 == ST[k][i]) ? IT[k][i] : IT[k][j-(1 << k)+1];
		
		return std::make_pair(ans1, ans2);
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
	std::vector<std::pair<int, int>> ans(k);
	for (int i = 0; i < k; i++) {
		int l = 0, r = 0;
		std::cin >> l >> r;
		ans[i] = rmq.find_max(l, r);
	}
	for (int i = 0; i < k; i++) {
		std::cout << ans[i].second << " " << ans[i].first << std::endl;
	}
	return 0;
}

