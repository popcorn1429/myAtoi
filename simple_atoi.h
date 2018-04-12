#ifndef _SIMPLE_ATOI_H_
#define _SIMPLE_ATOI_H_

/*
实现atoi
原题默认只处理十进制的数字
因此 "0x3a" 不要求算成 58，结果只需要是 0 即可
但是下面的实现比较复杂且会判断字符串是否属于十六进制或者八进制
如果第一个字符是正负号，则只能以十进制处理
如果十进制数第一个字符是'0'，就会得到0，后面的数字不再处理
例如 "-022" 不会得到 -22 ，而是得到 0

如果以 "0x" 开头，按十六进制处理 a-f A-F 可以混用
如果以 '0' 开头，按八进制处理，这就是为什么十进制的第一个数字不能使0的原因，要跟八进制区分开
*/

#include <string>
#include <climits>
using namespace std;

class Solution {
public:
    enum class Radix {
        Binary,
        Octonary,
        Decimalism,
        Hexadecimal
    };

    int myAtoi(string str) {
        if (str.empty())
            return 0;

        const char* src = str.c_str();
        char c = src[0];
        if ('+' == c || '-' == c) {
            //Decimal
            long v = getDecimalValue(src + 1);
            return ('-' == c) ? -v : v;
        }
        else if ('0' == c) {
            //Octonary or Hexadecimal
            if (str.size() > 1) {
                if ('x' == str[1]) {
                    //Hex
                    return getHexValue(src + 2);
                }
                else {
                    //Oct
                    return getOctValue(src + 1);
                }
            }
            else
                return 0;
        }
        else if ('1' <= c && c <= '9') {
            //Decimal
            return getDecimalValue(src);
        }
        else {
            // not a number
            return 0;
        }
    }

    inline bool isDigitChar(char c, Radix r) {
        switch (r)
        {
        case Radix::Binary:
            return c == '0' || c == '1';
        case Radix::Octonary:
            return c >= '0' && c <= '7';
        case Radix::Decimalism:
            return c >= '0' && c <= '9';
        case Radix::Hexadecimal:
            return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
        default:
            break;
        }
        return false;
    }

    long getDecimalValue(const char* src) {
        long number = 0;
        const char* p = src;
        if (*p != '\0' && *p != '0') {
            number = *p - '0';
            while (*(++p) != '\0' && isDigitChar(*p, Radix::Decimalism)) {
                number *= 10;
                number += *p - '0';
                if (number > INT_MAX)
                    return 0;
            }
        }
        return number;
    }

    long getOctValue(const char* src) {
        long number = 0;
        const char* p = src;
        if (isDigitChar(*p, Radix::Octonary) && *p != '0') {
            number = *p - '0';
            while (*(++p) != '\0' && isDigitChar(*p, Radix::Octonary)) {
                number *= 8;
                number += *p - '0';
                if (number > INT_MAX)
                    return 0;
            }
        }
        return number;
    }

    long getHexValue(const char* src) {
        long number = 0;
        const char* p = src;
        if (isDigitChar(*p, Radix::Hexadecimal)) {
            number = hexCharToNumber(*p);
            while (*(++p) != '\0' && isDigitChar(*p, Radix::Hexadecimal)) {
                number *= 16;
                number += hexCharToNumber(*p);
                if (number > INT_MAX)
                    return 0;
            }
        }
        return number;
    }

    long hexCharToNumber(char c) {
        switch (c)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return c - '0';
        case 'a':
        case 'A':
            return 10;
        case 'b':
        case 'B':
            return 11;
        case 'c':
        case 'C':
            return 12;
        case 'd':
        case 'D':
            return 13;
        case 'e':
        case 'E':
            return 14;
        case 'f':
        case 'F':
            return 15;
        default:
            break;
        }
        return 0;
    }
};

long simple_get_decimal(const char* src) {
    long number = 0;
    const char* p = src;
    while (*p >= '0' && *p <= '9') {
        number *= 10;
        number += *p - '0';
        if (number > INT_MAX+1)
            return INT_MAX + 1;

        ++p;
    }
    return number;
}

int simple_convert(const string& str) {
    //only treat str as a decimal number
    if (str.empty())
        return 0;

    long number = 0;
    const char* src = str.c_str();
    const char* p = src;
    while (*p == ' ' || *p == '\t' || *p == '\n')
    {
        ++p;
    }

    char first = *p;
    if (first == '+' || first == '-') {
        long v = simple_get_decimal(p+1);
        if ('+' == first && v > INT_MAX)
            return 0;
        else if ('-' == first)
            return -v;
        return v;
    }
    else if (first >= '0' && first <= '9') {
        long v = simple_get_decimal(p);
        if (v > INT_MAX)
            return INT_MAX;
        return v;
    }
    else {
        return 0;
    }
}


#endif