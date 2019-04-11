#include <iostream>
#include <vector>
#include <string>
#include <list>

std::vector<int> compute_p(std::string &s) {
    std::vector<int> p(s.length(), 0);
    for (int i = 1; i < p.size(); i++) {
        int j = p[i-1];
        while (j > 0 && s[j] != s[i]) 
            j = p[j-1];
        if (s[i] == s[j])
            j++;
        p[i] = j;
    }
    return p;
}

std::list<int> get_in(const std::string &s0, const std::string &s1) {
    std::string s = s1+'$'+s0;
    std::vector<int> p = compute_p(s);
    std::list<int> ans;
    for (int i = s1.length()+1; i < p.size(); i++) {
        if (p[i] == s1.length())
            ans.push_back(i-2*s1.length());
    }
    return ans;
}

int main() {
    std::string s0, s1;
    std::cin >> s0 >> s1;
    std::list<int> ans = get_in(s0, s1);
    for (auto i = ans.begin(); i != ans.end(); ++i) {
        std::cout << *i << std::endl;
    }
    return 0;
}
