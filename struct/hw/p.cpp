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
	std::string s;
	std::getline(std::cin, s);
	std::vector<int> p = compute_prefix(s);
	for (int i = 0; i < p.size(); i++) {
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
