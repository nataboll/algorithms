#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

std::vector<int> get_z(const std::string &s) {
    std::vector<int> z(s.length(), 0);
    z[0] = s.length();
    int l = 0, r = 0;
    for (int i = 1; i < z.size(); i++) {
        if (i <= r)
            z[i] = std::min(r-i+1, z[i-l]);
        while (z[i]+i < s.length() && s[z[i]] == s[i+z[i]])
            z[i]++;
        if (i+z[i]-1 > r) {
            l = i;
            r = z[i]+i-1;
        }
    }
    return z;
}

std::list<int> get_in(const std::string &s0, const std::string &s1) {
    std::list<int> in;
    std::string s = s1+'$'+s0;
    std::vector<int> z = get_z(s);
    for (int i = s1.length()+1; i < z.size(); i++) {
        if (z[i] == s1.length())
            in.push_back(i-s1.length()-1);
    }
    return in;
}

int main() {
    std::string s0, s1;
    std::cin >> s0 >> s1;
    std::list<int> in = get_in(s0, s1);
    for (auto i : in) {
        std::cout << i << std::endl;
    }
    return 0;
}
