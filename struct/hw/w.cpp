#include <iostream>
#include <string>
#include <vector>

std::vector<int> compute_prefix(std::string &s) {
	std::vector<int> p(s.length(), 0);
	for (int i = 1; i < s.length(); i++) {
		int j = p[i-1];
		while (j > 0 && s[i] != s[j])
			j = p[j-1];
		if (s[i] == s[j]) 
			j++;
		p[i] = j;
	}
	return p;
}

int main() {
	std::string s1, s2;
	std::cin >> s1 >> s2;
	s1 += '$';
	int n = s1.length();
	s1 += s2;
	std::vector<int> p = compute_prefix(s1);
	for (int i = n; i < s1.length(); i++) {
		if (p[i] == 0) {
                        std::cout << "Yes" << std::endl;
                        return 0;
                }
	}
	std::cout << "No" << std::endl;
	int k = 0;
	for (int i = n; i < s1.length(); i++) {
		if (p[i] > k) {
			k = p[i];
			continue;
		} else {
			std::cout << s1.substr(0, k-p[i]+1) << " ";
			k = p[i];
		}
	}
	std::cout << s1.substr(0, p[s1.length()-1]) << " ";
	std::cout << std::endl;
	return 0;
}
