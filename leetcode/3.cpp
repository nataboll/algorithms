#include <iostream>
#include <unordered_map>
#include <string>

class Solution {
    int max = 1;

public:
    int lengthOfLongestSubstring(std::string s) {
        if (s.length() == 0)
            return 0;
        std::unordered_map<char, int> used;
        int counter = 0;
        int start = 0;
        for (int i = 0; i < s.length(); i++) {
            if (used.find(s[i]) == used.end() || used[s[i]] < start) {
                counter++;
                max = std::max(counter, max);
            } else {
                max = std::max(counter, max);
                start = used[s[i]] + 1;
                counter = i - start + 1;
            }
            used[s[i]] = i;
        }
        return max;
    }
};

int main()  {
    std::string s;
    std::cin >> s;
    Solution sol;
    std::cout << sol.lengthOfLongestSubstring(s) << std::endl;
    return 0;
}
