//
// Created by fanis on 11.10.2020.
//

#ifndef LONG_ARITHMETIC_LONGNUM_H
#define LONG_ARITHMETIC_LONGNUM_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

namespace num{
    class longNum{
    protected:
        std::vector<int> num;
        bool sign;


        longNum left_shift(longNum number, int x);
    public:
        longNum div2();
        longNum();

        explicit longNum(std::vector<int>& n, bool sig);

        explicit longNum(int n);

        explicit longNum(std::string& s);

        ~longNum();

        int size();

        longNum operator+(const longNum number);

        longNum operator-(const longNum number);

        longNum operator-();

        longNum operator*(int x);

        longNum operator*(longNum number);

        longNum operator/(longNum number);

        longNum operator%(longNum number);

        bool operator>(longNum number);

        bool operator<(longNum number);

        bool operator==(longNum number);

        bool operator>=(longNum number);

        bool operator<=(longNum number);

        bool operator!=(longNum number);

        friend std::ostream& operator<<(std::ostream& out, const longNum& number);

        friend longNum operator+=(longNum& number1, const longNum& number2);
    };


    longNum operator+=(longNum& number1, const longNum& number2);

}



#endif //LONG_ARITHMETIC_LONGNUM_H
