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
	std::string s;
	std::cin >> s;
	std::vector<int> z = compute_z(s);
	for (int i = 0; i < z.size();  i++) 
		std::cout << z[i] << " ";
	std::cout << std::endl;
	return 0;
}
