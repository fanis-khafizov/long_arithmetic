#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class longNum{
private:
    vector<int> num;
    bool sign;

    longNum left_shift(longNum number, int x) {
        number.num.insert(number.num.begin(), x, 0);
        //for (int i = number.num.size() - 1; i >= 0; i--) cout << number.num[i];
        return number;
    }
public:
    longNum() : sign(true) {};

    longNum(vector<int>& n, bool sig = true) : num(n), sign(sig) {}

    explicit longNum(int n) {
        sign = n >= 0;
        if (n == 0) num.push_back(0);
        n = abs(n);
        while (n > 0) {
            num.push_back(n % 10);
            n /= 10;
        }
    }

    explicit longNum(string& s) {
        sign = s[0] != '-';
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

    longNum operator+(const longNum& number) {
        longNum first = *this;
        longNum second = number;
        first.sign = true;
        second.sign = true;
        if (!sign){
            if (!number.sign) {
                longNum res = first + second;
                res.sign = false;
                return res;
            } else {
                longNum res = second - first;
                return res;
            }
        } else {
            if (!number.sign) {
                longNum res = first - second;
                return res;
            }
        }
        if (first >= second) {
            for (int i = 0; i <= second.size() - 1; i++) {
                if ((i == first.size() - 1) && (first.num[i] + second.num[i] >= 10)) {
                    first.num.push_back(1);
                } else {
                    first.num[i + 1] += ((first.num[i] + second.num[i]) >= 10);
                }
                first.num[i] = (first.num[i] + second.num[i]) % 10;
            }

            return first;
        }
        return second + first;
    }

    longNum operator-(const longNum& number) {
        longNum first = *this;
        longNum second = number;
        first.sign = true;
        second.sign = true;
        if (!sign) {
            if (!number.sign){
                longNum res = second - first;
                return res;
            } else {
                longNum res = first + second;
                res.sign = false;
                return res;
            }
        } else {
            if (!number.sign) {
                longNum res = first + second;
                res.sign = true;
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
        res.sign = false;
        return res;
    }

    longNum operator-() {
        longNum res = *this;
        res.sign = !res.sign;
        return res;
    }

    longNum operator*(int x) {
        vector<int> vec(num.size(), 0);
        for (int i = 0; i < num.size() - 1; i++) {
            vec[i + 1] = (vec[i] + num[i] * x) / 10;
            vec[i] = (vec[i] + num[i] * x) % 10;
        }
        if (num[num.size() - 1] * x + vec[vec.size() - 1] >= 10) {
            vec.push_back((num[num.size() - 1] * x + vec[vec.size() - 1]) / 10);
            vec[vec.size() - 2] = (vec[vec.size() - 2] + num[num.size() - 1] * x) % 10;

        } else {
            vec[vec.size() - 1] = vec[vec.size() - 1] + num[num.size() - 1] * x;
        }
        while (vec[vec.size() - 1] == 0 && vec.size() > 1) vec.pop_back();
        longNum res(vec);
        return res;
    }

    longNum operator*(longNum& number) {
        longNum first = *this;
        longNum second = number;
        first.sign = true;
        second.sign = true;

        longNum ans(0);

        for (int i = 0; i < first.size(); i++) {
            ans = ans + left_shift(second * first.num[i], i);
        }
        ans.sign = !(sign ^ number.sign);
        return ans;
    }

    bool operator>(longNum& number) {
        if (sign > number.sign) return true;
        if (sign < number.sign) return false;
        if (num.size() > number.size()) return sign;
        if (num.size() < number.size()) return !sign;
        for (int i = num.size() - 1; i >= 0; i--) {
            if (num[i] > number.num[i]) return sign;
            if (num[i] < number.num[i]) return !sign;
        }
        return false;
    }

    bool operator<(longNum& number) {
        if (sign > number.sign) return false;
        if (sign < number.sign) return true;
        if (num.size() < number.size()) return sign;
        if (num.size() > number.size()) return !sign;
        for (int i = num.size() - 1; i >= 0; i--) {
            if (num[i] < number.num[i]) return sign;
            if (num[i] > number.num[i]) return !sign;
        }
        return false;
    }

    bool operator==(longNum& number) {
        /*
        if (sign != number.sign) return 0;
        if (num.size() != number.size()) return 0;
        for (int i = num.size() - 1; i >= 0; i--)
            if (num[i] != number.num[i]) return 0;
        return 1;
         */
        return !((*this > number) || (*this < number));
    }

    bool operator>=(longNum& number) {
        return !(*this < number);
    }

    bool operator<=(longNum& number) {
        return !(*this > number);
    }

    friend ostream& operator<<(ostream &out, const longNum& number);
    friend longNum operator+=(longNum& number1, const longNum& number2);
};

ostream& operator<<(ostream &out, const longNum& number) {
    if (!number.sign) out << '-';
    for (int i = number.num.size() - 1; i >= 0; i--) out << number.num[i];
    return out;
}

longNum operator+=(longNum& number1, const longNum& number2) {
    number1 = number1 + number2;
    return number1;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    longNum n1(s1);
    longNum n2(s2);
    cout << n1 + n2 << endl;
    cout << n1 - n2 << endl;
    cout << n1 * n2 << endl;
    return 0;
}
