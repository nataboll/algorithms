#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <climits>
#include <algorithm>

template<class T>
class segment_tree {
public:
	using Data = std::pair<T, T>;	// add and sum
	
private:
	int n;
	std::vector<Data> tree;

public:
	segment_tree(int _n) : tree(_n, std::make_pair(0, 0))
			     , n(_n)
	{
                n = (1 << (int)(std::log2(n-1)+1));
                tree.resize(2*n, std::make_pair(0, 0));
	}

	T rsq(int l, int r) const {
		l += (n-1);
		r += (n-1);
		T ans = 0;
		while (l <= r) {
			if (l&1) {
				ans += tree[l].second;
			}
			if (!(r&1)) {
				ans += tree[r].second;
			}
			l = ((l+1)/2);
			r = ((r-1)/2);
		}
		return ans;
	}

	void update(int l, int r, T d) {
                l += (n-1);
                r += (n-1);
                while (l <= r) {
                        if (l&1) {
                                tree[l].first += d;
                        }
                        if (!(r&1)) {
                                tree[r].first += d;
                        }
                        l = ((l+1)/2);
                        r = ((r-1)/2);
                }
        }

	void spread_updates() {
		for (int i = 1; i < n; i++) {
			tree[2*i].first += tree[i].first;
                        tree[2*i+1].first += tree[i].first;
		}
	}

	void relax() {
		spread_updates();
		for (int i = n; i < 2*n; i++) {
			tree[i].second = tree[i].first;
		}
		for (int i = n-1; i > 0; i--) {
			tree[i].second += (tree[2*i].second + tree[2*i+1].second); 
		}
	}
};

template<class T>
class Random {
private:
        T curr;
        T a;
        T b;

public:
        Random(T _a, T _b) : a(_a)
                           , b(_b)
                           , curr((T)0)
        {}

        T next_rand() {
                curr = curr * a + b;
                return curr >> 8;
        }
};

template<class T>
struct Update {
	int l;
	int r;
	T add;

	Update() : l(0)
		 , r(0)
		 , add(0)
	{}

	Update(int _l, int _r, T _add) : l(_l)
				       , r(_r)
				       , add(_add)
	{}
};

int main() {	
	int m = 0, q = 0;
        unsigned a = 0, b = 0;
        std::cin >> m >> q >> a >> b;

        unsigned res = 0;
        Random<unsigned> rand(a, b);

	std::vector<Update<unsigned>> updates(m);
        int max = 0;
        for (int i = 0; i < m; i++) { // m*log(n)
                unsigned add = rand.next_rand();
                int l = (int)rand.next_rand();
                int r = (int)rand.next_rand();
                if (l > r)
                        std::swap(l, r);
                max = std::max(max, r);
                updates[i] = Update<unsigned>(l, r, add);
        }

	segment_tree<unsigned> rsq(max);

	for (int i = 0; i < updates.size(); i++) {
		rsq.update(updates[i].l, updates[i].r, updates[i].add);
	}

	rsq.relax();

        for (int i = 0; i < q; i++) {   // q*log(n)
                int l = (int)rand.next_rand();
                int r = (int)rand.next_rand();
                if (l > r)
                        std::swap(l, r);
                res += rsq.rsq(l, r);
        }

        std::cout << res << std::endl;

	return 0;
}
