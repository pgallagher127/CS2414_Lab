#include <iostream>
using namespace std;

class Solution{
public:
    int translateRomantoNum(char c);
    int romanToInt(string s);
};

int Solution::translateRomantoNum(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return -1;
    }
}

int Solution::romanToInt(string s) {
    int total = 0;
    for (int i = 0; i < s.length(); i++) {
        if (i == s.length()-1) {
            total += translateRomantoNum(s[i]);
            break;
        }
        if (translateRomantoNum(s[i]) < translateRomantoNum(s[i+1])) {
            total += translateRomantoNum(s[i+1]) - translateRomantoNum(s[i]);
            i++;
        }
        else {
            total += translateRomantoNum(s[i]);
        }
        

    }
    return total;
}

int main() {
    string roman;
    cin >> roman;

    Solution sol;
    cout << "Int Value Of " << roman << " is " << sol.romanToInt(roman) << endl;
    return 0;
}