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

std::vector<int> kmp(std::string &s, std::string &t) {	// find s in t
	std::vector<int> p = compute_prefix(s);
	std::vector<int> res;
	int k = 0;
	for (int i = 0; i < t.length(); i++) {
		while ((k > 0) && (s[k] != t[i]))
			k = p[k-1];
		if (s[k] == t[i])
			k++;
		if (k == s.length())
			res.push_back(i - s.length() + 1);
	}
    	return res;
}

int main() {
	std::string s, t;
	std::getline(std::cin, t);
	std::getline(std::cin, s);
	std::vector<int> res = kmp(s, t);
	for (int i = 0; i < res.size(); i++) {
		std::cout << res[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
