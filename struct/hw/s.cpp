#include <iostream>
#include <string>
#include <vector>

std::vector<int> compute_z(std::string &s) {
	std::vector<int> z(s.length());
	int l = 0, r = 0;
	z[0] = 0;
	for (int i = 1; i < s.length(); i++) {
		if (i <= r)
			z[i] = std::min(r-i+1, z[i-l]);
		while (i + z[i] < s.length() && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	return z;
}

int count_substr(std::string &s) {
	std::string t;
	t += s[0];
	int k = 1;	// first letter
	for (int i = 1; i < s.length(); i++) {
		t = s[i] + t;
		std::vector<int> z = compute_z(t);
		int max = 0;
		for (int j = 0; j < z.size(); j++) {
			if (z[j] > max)
				max = z[j];
		}
		k += (t.length() - max);
	}
	return k;
}

int main() {
	std::string s;
	std::cin >> s;
	std::cout << count_substr(s) << std::endl;
	return 0;
}
