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

int kmp(std::string s, std::string t) {	// find s in t
	std::vector<int> p = compute_prefix(s);
	int k = 0;
	for (int i = 0; i < t.length(); i++) {
		while ((k > 0) && (s[k] != t[i]))
			k = p[k-1];
		if (s[k] == t[i])
			k++;
		if (k == s.length())
			return (i - s.length() + 1);
	}
    	return -1;
}

int main() {
	int n = 0;
	std::cin >> n;
	std::string s1, s2;
	std::cin >> s1 >> s2;
	s2 += '1';
	s2 += s2;
//	std::cout << s2 << std::endl;
	int res1 = kmp(s1, s2);	
	s2[n-1] = s2[2*n-1] = '0';
//	std::cout << s2 << std::endl;
	int res0 = kmp(s1, s2);
//	std::cout << res1 << " " << res0 << std::endl;
	if (res0 == 0 || res1 == 0 || (res1 > 0 && res0 > 0)) 
		std::cout << "Random" << std::endl;
	else if (res0 > 0)
		std::cout << "No" << std::endl;
	else if (res1 > 0)
		std::cout << "Yes" << std::endl;
	return 0;
}

