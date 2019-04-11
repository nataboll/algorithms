#include <string>
#include <iostream>
#include <vector>

class Solution {
private:
    
    std::vector<int> compute_z(std::string &s) {
        std::vector<int> z(s.length(), 0);
        int l = 0, r = 0;
        z[0] = s.length();
        for (int i = 1; i < s.length(); i++) {
            if (i <= r)
                z[i] = std::min(r-i+1, z[i-l]);
            
            while (i+z[i] < s.length() && s[z[i]] == s[i+z[i]])
                z[i]++;
            
            if (i+z[i]-1 > r) {
                r = i+z[i]-1;
                l = i;
            }
        }
        return z;
    }
    
    std::vector<int> compute_a(std::string &s) {
        std::vector<int> a(s.length());
        std::string s1(s);
        for (int i = 0; i < s.length(); i++)
            s1 += s[s.length()-1-i];
        std::vector<int> a_full = compute_z(s1);
        for (int i = 2*s.length()-1; i >= s.length(); i--)
            a[2*s.length()-1-i] = a_full[i];
        return a;
    }
    
public:
    std::string shortestPalindrome(std::string s) {
        std::vector<int> a = compute_a(s);
        int r = 0;
        for (int i = a.size()-1; i >= 0; i--) {
            if (a[i] == i+1) {
                r = i;
                break;
            }
        }
        std::string ans;
        for (int i = s.length()-1; i > r; i--) 
            ans += s[i];
        ans += s;
        return ans;
    }
};

int main() {
    std::string s;
    std::cin >> s;
    Solution sol;
    s = sol.shortestPalindrome(s);
    std::cout << s << std::endl;
    return 0;
}
