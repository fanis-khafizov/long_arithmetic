#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class longNum{
private:
    vector<int> num;
    bool sign;
public:
    longNum() : sign(1) {};

    longNum(vector<int>& n, bool sig = true) : num(n), sign(sig) {}

    longNum(int n) {
        sign = n >= 0;
        if (n == 0) num.push_back(0);
        n = abs(n);
        while (n > 0) {
            num.push_back(n % 10);
            n /= 10;
        }
    }

    longNum(string& s) {
        sign = (s[0] == '-' ? false : true);
        for (int i = s.length() - 1; i >= !sign; i--) {
            num.push_back(s[i] - '0');
        }
    }

    ~longNum() {
        num.clear();
    }

    int size() {
        return num.size();
    }

    longNum operator+(longNum& number) {
        longNum first = *this;
        longNum second = number;
        first.sign = true;
        second.sign = true;
        if (sign == false){
            if (number.sign == false) {
                longNum res = first + second;
                res.sign = false;
                return res;
            } else {
                longNum res = second - first;
                return res;
            }
        } else {
            if (number.sign == false) {
                longNum res = first - second;
                return res;
            }
        }
        if (first >= second) {
            for (int i = 0; i <= second.size() - 1; i++) {
                first.num[i] = (first.num[i] + second.num[i]) % 10;
                if (i == first.size() - 1) {
                    if (first.num[i] + second.num[i] >= 10) first.num.push_back(1);
                    break;
                }
                first.num[i + 1] += (first.num[i] + second.num[i] >= 10);
            }
            return first;
        }
        return second + first;
    }

    longNum operator-(longNum& number) {
        longNum first = *this;
        longNum second = number;
        first.sign = true;
        second.sign = true;
        if (sign == false) {
            if (number.sign == false){
                longNum res = second - first;
                return res;
            } else {
                longNum res = first + second;
                res.sign = false;
                return res;
            }
        } else {
            if (number.sign == false) {
                longNum res = first + second;
                res.sign = false;
                return res;
            }
        }
        if (first == second) return longNum(0);
        if (first > second) {
            for (int i = 0; i <= second.size() - 1; i++) {
                if (i < first.size() - 1) first.num[i + 1] -= (first.num[i] < second.num[i]);
                first.num[i] = (first.num[i] >= second.num[i] ? first.num[i] - second.num[i] : 10 + first.num[i] - second.num[i]);
            }
            while (first.num[first.num.size() - 1] == 0) first.num.pop_back();
            return first;
        }
        longNum res = second - first;
        res.sign = 0;
        return res;
    }

    bool operator>(longNum& number) {
        if (sign > number.sign) return 1;
        if (sign < number.sign) return 0;
        if (num.size() > number.size()) return sign;
        if (num.size() < number.size()) return !sign;
        for (int i = num.size() - 1; i >= 0; i--) {
            if (num[i] > number.num[i]) return sign;
            if (num[i] < number.num[i]) return !sign;
        }
        return 0;
    }

    bool operator<(longNum& number) {
        if (sign > number.sign) return 0;
        if (sign < number.sign) return 1;
        if (num.size() < number.size()) return sign;
        if (num.size() > number.size()) return !sign;
        for (int i = num.size() - 1; i >= 0; i--) {
            if (num[i] < number.num[i]) return sign;
            if (num[i] > number.num[i]) return !sign;
        }
        return 0;
    }

    bool operator==(longNum& number) {
        if (sign != number.sign) return 0;
        if (num.size() != number.size()) return 0;
        for (int i = num.size() - 1; i >= 0; i--)
            if (num[i] != number.num[i]) return 0;
        return 1;
    }

    bool operator>=(longNum& number) {
        return !(*this < number);
    }

    bool operator<=(longNum& number) {
        return !(*this > number);
    }

    void print() {
        if (!sign) cout << '-';
        for (int i = num.size() - 1; i >= 0; i--) cout << num[i];
        cout << endl;
    }
};

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    longNum n1(s1);
    longNum n2(s2);
    (n1 + n2).print();
    return 0;
}
