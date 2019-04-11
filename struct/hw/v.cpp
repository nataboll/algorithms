#include <iostream>
#include <string>
#include <vector>
#include <set>

std::vector<int> compute_z(std::vector<int> &s) {
	std::vector<int> z(s.size());
	int l = 0, r = 0;
	z[0] = s.size();
	for (int i = 1; i < s.size(); i++) {
		if (i <= r)
			z[i] = std::min(r - i + 1, z[i-l]);
		while (i + z[i] < s.size() && s[z[i]] == s[i+z[i]])
			z[i]++;
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	return z;
}

std::vector<int> compute_a(int n, std::vector<int> &s) {
        for (int i = 0; i < n; i++) {
                s[i+n] = s[n-i-1];
        }
        std::vector<int> z = compute_z(s);
	std::vector<int> a(n);
	for (int i = z.size()-1; i >= n; i--) {
		a[z.size()-i-1] = z[i];
	}
	return a;
}

int main() {
	int n = 0, m = 0;;
	std::cin >> n >> m;
	std::vector<int> s(2*n);
	for (int i = 0; i < n; i++) {
		std::cin >> s[i];
	}
	std::vector<int> a = compute_a(n, s);
	std::set<int> ans;
	for (int i = a.size()-1; i >= 0;  i--) {
		if (!(a[i]&1) && a[i] == i+1)
			ans.insert(n - a[i]/2);
	}
	ans.insert(n);
	for (auto i : ans) 
		std::cout << i << " ";
	std::cout << std::endl;
	return 0;
}
