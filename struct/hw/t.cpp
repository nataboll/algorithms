#include <iostream>
#include <string>
#include <vector>

std::vector<int> compute_z(std::string &s) {
	std::vector<int> z(s.length());
	int l = 0, r = 0;
	z[0] = s.length();
	for (int i = 1; i < s.length(); i++) {
		if (i <= r)
			z[i] = std::min(r - i + 1, z[i-l]);
		while (i + z[i] < s.length() && s[z[i]] == s[i+z[i]])
			z[i]++;
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	return z;
}

int main() {
	int n = 0;
	std::cin >> n;
	std::string s;
	std::cin >> s;
	for (int i = 0; i < n; i++) {
		s += s[n-i-1];
	}
	std::vector<int> z = compute_z(s);
	for (int i = z.size()-1; i >= n;  i--) 
		std::cout << z[i] << " ";
	std::cout << std::endl;
	return 0;
}
