#include <iostream>
#include <vector>
#include <algorithm>	
#include <cmath>
#include <utility>
#include <string>

template<class Type>
class RMQ {
private:
	using Data = std::pair<Type, std::string>;	// length and rest

	std::vector<Data> T;
	std::vector<std::vector<Data>> ST;

	Data unite(Data a, Data b) const {
		a += b;
		std::string res;
		int max = 0;
		int counter = 0, l = 0;
		for (int i = 0; i < a.length(); i++) {
			if (counter == 0 && i != 0) {
				max = i-l+1;
			} else if (counter < 0) {
				counter = 0;
				l = i;
			}
			if (a[i] == '(') 
				counter++;
			else if (a[i] == ')')
				counter--;
		}



		return std::make_pair(0, std::string(1, '0'));
	}

	void initialize_ST() {
		int n = std::log2(T.size()); 
		n++;
	        ST = std::vector<std::vector<Data>>(n);
                ST[0] = T;
                for (int k = 1; k < ST.size(); k++) {
                        ST[k] = std::vector<Data>(ST[k-1].size()-(1 << (k-1)));
                        for (int i = 0; i < ST[k].size(); i++) {
                                ST[k][i] = unite(ST[k-1][i], ST[k-1][i+(1 << (k-1))]);
                        }
                }
	}

public:
	RMQ(std::string &s) {
		T = std::vector<Data>(s.length());
		for (int i = 0; i < s.length(); i++) {
			T[i] = std::make_pair(0, s[i]);
		}
		initialize_ST();
	}
	
	Type find_max(int i, int j) const {
		i--;
		j--;
		int k = std::log2(j-i+1);
		Data ans = unite(ST[k][i], ST[k][j-(1 << k)+1]);
		return ans.first;
	}
};

int main() {
        std::string s;
        std::cin >> s;
        int k = 0;
        std::cin >> k;
        std::vector<int> ans(k);
        RMQ<int> rmq(s);
        for (int i = 0; i < k; i++) {
                int l = 0, r = 0;
                std::cin >> l >> r;
                ans[i] = rmq.find_max(l, r);
        }
        for (int i = 0; i < ans.size(); i++) {
                std::cout << ans[i] << std::endl;
        }
        return 0;
}
